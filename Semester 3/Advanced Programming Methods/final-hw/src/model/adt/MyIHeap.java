package model.adt;

import model.values.Value;

import java.util.Map;

public interface MyIHeap {
    int allocate(Value value);
    Value get(int address);
    void update(int address, Value value);
    boolean isDefined(int address);
    void setContent(Map<Integer, Value> newHeap);
    Map<Integer, Value> getContent();
    String toString();
}
