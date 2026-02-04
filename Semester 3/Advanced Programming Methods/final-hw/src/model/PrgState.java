package model;

import exceptions.MyException;
import model.adt.MyIDictionary;
import model.adt.MyIHeap;
import model.adt.MyIList;
import model.adt.MyIStack;
import model.statements.IStmt;
import model.values.Value;
import java.io.BufferedReader;

public class PrgState {
    private MyIStack<IStmt> exeStack;
    private MyIDictionary<String, Value> symTable; //maps variable names to their values
    private MyIList<Value> out; //printed values
    private MyIDictionary<String, BufferedReader> fileTable; //maps file names to BufferedReaders
    private MyIHeap heap; //heap memory
    private int id;
    private static int nextId = 1;

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot, MyIDictionary<String, BufferedReader> ft, MyIHeap hp, IStmt prg) {
        this.exeStack = stk;
        this.symTable = symtbl;
        this.out = ot;
        this.fileTable = ft;
        this.heap = hp;
        this.id = generateNewId();
        stk.push(prg);
    }

    private static synchronized int generateNewId() {
        return nextId++;
    }

    public int getId() {
        return id;
    }

    public boolean isNotCompleted() {
        return !exeStack.isEmpty();
    }

    public PrgState oneStep() throws MyException {
        if (exeStack.isEmpty()) {
            throw new MyException("prgstate stack is empty");
        }
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }

    public MyIStack<IStmt> getStk() {
        return exeStack;
    }

    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }

    public MyIList<Value> getOut() {
        return out;
    }

    public MyIDictionary<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public MyIHeap getHeap() {
        return heap;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        sb.append("ID: ").append(id).append("\n");
        
        sb.append("ExeStack:\n");
        if (exeStack.isEmpty()) {
            sb.append("(empty)\n");
        } else {
            for (IStmt stmt : exeStack.getReversed()) {
                sb.append(stmt.toString()).append("\n");
            }
        }
        
        sb.append("SymTable:\n");
        if (symTable.getContent().isEmpty()) {
            sb.append("(empty)\n");
        } else {
            for (String key : symTable.getContent().keySet()) {
                sb.append(key).append(" --> ").append(symTable.getContent().get(key).toString()).append("\n");
            }
        }
        
        sb.append("Out:\n");
        if (out.getList().isEmpty()) {
            sb.append("(empty)\n");
        } else {
            for (Value val : out.getList()) {
                sb.append(val.toString()).append("\n");
            }
        }
        
        sb.append("FileTable:\n");
        if (fileTable.getContent().isEmpty()) {
            sb.append("(empty)\n");
        } else {
            for (String filename : fileTable.getContent().keySet()) {
                sb.append(filename).append("\n");
            }
        }
        
        sb.append("Heap:\n");
        if (heap.getContent().isEmpty()) {
            sb.append("(empty)\n");
        } else {
            for (Integer addr : heap.getContent().keySet()) {
                sb.append(addr).append(" -> ").append(heap.getContent().get(addr).toString()).append("\n");
            }
        }
        
        return sb.toString();
    }
}
