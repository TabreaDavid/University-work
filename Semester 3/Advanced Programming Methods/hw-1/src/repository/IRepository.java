package repository;

import model.FruitTree;

public interface IRepository {
    
    void add(FruitTree tree);

    boolean remove(FruitTree tree);

    FruitTree[] getAll();

    int size();

    boolean isEmpty();

    boolean isFull();
}   
