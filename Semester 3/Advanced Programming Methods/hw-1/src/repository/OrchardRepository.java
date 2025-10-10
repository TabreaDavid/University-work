package repository;

import model.FruitTree;

public class OrchardRepository implements IRepository {
    private int maxSize = 50;
    private FruitTree[] trees;
    private int currentSize;

    public OrchardRepository(){
        this.trees = new FruitTree[maxSize];
        this.currentSize = 0;
    }

    public boolean isFull(){
        return this.currentSize >= maxSize;
    }

    public void add(FruitTree tree){
        if (isFull() ){
            throw new RuntimeException("Repository is full!");
        }

        trees[currentSize++] = tree;
    }

    public boolean remove(FruitTree tree){
        for (int i = 0; i < currentSize; i++){
            if (trees[i] == tree){
                for (int j = i; j < currentSize - 1; j++){
                    trees[j] = trees[j + 1];
                }
                trees[--currentSize] = null;
                return true;
            }
        }
        return false;
    }

    public FruitTree[] getAll(){
        return trees;
    }

    public boolean isEmpty(){
        return currentSize == 0;
    }

    public int size(){
        return currentSize;
    }
}
