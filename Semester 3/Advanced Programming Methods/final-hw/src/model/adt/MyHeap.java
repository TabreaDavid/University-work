package model.adt;

import model.values.Value;

import java.util.HashMap;
import java.util.Map;

public class MyHeap implements MyIHeap {
    private Map<Integer, Value> heap;
    private int freeLocation;

    public MyHeap() {
        this.heap = new HashMap<>();
        this.freeLocation = 1;
    }

    @Override
    public int allocate(Value value) {
        int address = freeLocation;
        heap.put(address, value);
        freeLocation++;
        return address;
    }

    @Override
    public Value get(int address) {
        return heap.get(address);
    }

    @Override
    public void update(int address, Value value) {
        heap.put(address, value);
    }

    @Override
    public boolean isDefined(int address) {
        return heap.containsKey(address);
    }

    @Override
    public void setContent(Map<Integer, Value> newHeap) {
        this.heap = newHeap;
    }

    @Override
    public Map<Integer, Value> getContent() {
        return heap;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("Heap:\n");
        for (Map.Entry<Integer, Value> entry : heap.entrySet()) {
            result.append(entry.getKey()).append(" -> ").append(entry.getValue()).append("\n");
        }
        return result.toString();
    }
}
