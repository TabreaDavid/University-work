package controller;

import exceptions.MyException;
import model.PrgState;
import model.values.RefValue;
import model.values.Value;
import repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private final IRepository repo;
    private ExecutorService executor;

    public Controller(IRepository repo) {
        this.repo = repo;
    }

    public IRepository getRepository() {
        return repo;
    }

    private List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddr();
                })
                .collect(Collectors.toList());
    }

    private List<Integer> getAddrFromHeap(Collection<Value> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {
                    RefValue v1 = (RefValue) v;
                    return v1.getAddr();
                })
                .collect(Collectors.toList());
    }

    private Map<Integer, Value> conservativeGarbageCollector(List<Integer> symTableAddr, List<Integer> heapAddr, Map<Integer, Value> heap) {
        List<Integer> allReferencedAddresses = Stream.concat(symTableAddr.stream(), heapAddr.stream())
                .distinct()
                .collect(Collectors.toList());
        
        return heap.entrySet().stream()
                .filter(e -> allReferencedAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private List<PrgState> removeCompletedPrg(List<PrgState> inPrgList) {
        return inPrgList.stream()
                .filter(p -> p.isNotCompleted())
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<PrgState> prgList) throws MyException, InterruptedException {
        // Remove completed programs first
        prgList = removeCompletedPrg(prgList);
        
        if (prgList.isEmpty()) {
            repo.setPrgList(prgList);
            return;
        }
        
        // Garbage collection
        List<Integer> allSymTableAddresses = prgList.stream()
                .flatMap(p -> getAddrFromSymTable(p.getSymTable().getContent().values()).stream())
                .distinct()
                .collect(Collectors.toList());
        
        Map<Integer, Value> heap = prgList.get(0).getHeap().getContent();
        List<Integer> heapAddresses = getAddrFromHeap(heap.values());
        
        prgList.get(0).getHeap().setContent(
            conservativeGarbageCollector(allSymTableAddresses, heapAddresses, heap)
        );
        
        // Log before execution
        for (PrgState prg : prgList) {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyException e) {
                System.err.println("Error logging program state: " + e.getMessage());
            }
        }
        
        // Create executor if needed
        if (executor == null || executor.isShutdown()) {
            executor = Executors.newFixedThreadPool(2);
        }

        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>) (() -> {
                    return p.oneStep();
                }))
                .collect(Collectors.toList());

        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        System.err.println("Error executing program state: " + e.getMessage());
                        return null;
                    }
                })
                .filter(p -> p != null)
                .collect(Collectors.toList());

        prgList.addAll(newPrgList);
        
        // Remove completed programs
        prgList = removeCompletedPrg(prgList);

        // Log after execution
        for (PrgState prg : prgList) {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyException e) {
                System.err.println("Error logging program state: " + e.getMessage());
            }
        }

        repo.setPrgList(prgList);
    }

    public void allStep() throws MyException, InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());
        
        while (prgList.size() > 0) {
            oneStepForAllPrg(prgList);
            prgList = removeCompletedPrg(repo.getPrgList());
        }
        
        executor.shutdownNow();
        
        repo.setPrgList(prgList);
    }
}
