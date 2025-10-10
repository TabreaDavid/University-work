
import controller.OrchardController;
import repository.OrchardRepository;
import view.OrchardView;
import model.*;

public class Main {
    public static void main(String[] args) {
        OrchardRepository repository = new OrchardRepository();
        OrchardController controller = new OrchardController(repository);
        OrchardView view = new OrchardView(controller);

        populateRepository(controller);

        view.displayAllTrees();

        view.displayTreesOlderThan3Years();
    }

    static void populateRepository(OrchardController controller) {
        controller.addTree(new AppleTree(5, "Apple tree 1"));
        controller.addTree(new AppleTree(2, "Apple tree 2"));
        controller.addTree(new CherryTree(5, "Cherry tree 1"));
        controller.addTree(new CherryTree(2, "Cherry tree 2"));
        controller.addTree(new PearTree(5, "Pear tree 1"));
        controller.addTree(new PearTree(2, "Pear tree 2"));

    }
}
