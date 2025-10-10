package view;

import controller.OrchardController;
import model.FruitTree;

public class OrchardView {
    private OrchardController controller;

    public OrchardView(OrchardController controller) {
        this.controller = controller;
    }

    public void displayTreesOlderThan3Years() {
        FruitTree[] trees = controller.getTreesOlderThan(3);
        IO.println("===Trees older than 3 years===");
        for (FruitTree tree : trees) {
            if (tree != null) {
                IO.println(tree.toString());
            }
        }
    }

    public void displayAllTrees() {
        FruitTree[] trees = controller.getAll();
        IO.println("===All trees===");
        for (FruitTree tree : trees) {
            if (tree != null) {
                IO.println(tree.toString());
            }
        }
    }
}
