package controller;

import repository.IRepository;
import model.FruitTree;

public class OrchardController {
    private IRepository repository;

    public OrchardController(IRepository repository){
        this.repository = repository;
    }

    public void addTree(FruitTree tree){
        try {
        repository.add(tree);
        } catch (Exception e) {
            throw new RuntimeException(e.getMessage());
        }
    }

    public boolean removeTree(FruitTree tree){
        return repository.remove(tree);
    }

    public FruitTree[] getAll(){
        return repository.getAll();
    }

    public FruitTree[] getTreesOlderThan(int age){
        FruitTree[] resultTree = new FruitTree[repository.size()];
        FruitTree[] trees = getAll();
        int k = 0;
        for (int i = 0; i < repository.size(); i++){
            if (trees[i].isOlderThan(age)){
                resultTree[k++] = trees[i];
            }
        }

        return resultTree;
    }
    
}
