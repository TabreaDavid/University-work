#include <stdio.h>
#include <stdlib.h>
#include "repository.h"
#include "controller.h"
#include "ui.h"
#include "test.h"

int main() {
    Repository *repo = createRepository();
    Controller *controller = malloc(sizeof(Controller));
    controller->repo = repo;
    controller->undoStack.index = 0;
    controller->redoStack.index = 0;

    testAddMaterial(controller);
    testRemoveMaterial(controller);
    testUpdateMaterial(controller);

    Ui *ui = malloc(sizeof(Ui));
    ui->controller = controller;

    addMaterialService(ui->controller, "Flour", "GrainCo Ltd.", 500, 20250715);
    addMaterialService(ui->controller, "Sugar", "SweetSource Inc.", 300, 20250610);
    addMaterialService(ui->controller, "Butter", "DairyFresh Supplies", 200, 20250425);
    addMaterialService(ui->controller, "Eggs", "FarmBest Produce", 1000, 20250330);
    addMaterialService(ui->controller, "Milk", "PureDairy Distributors", 200, 20250320);
    addMaterialService(ui->controller, "Yeast", "BakeWell Ingredients", 50, 20250905);
    addMaterialService(ui->controller, "Baking Powder", "RiseUp Chemicals", 75, 20250818);
    addMaterialService(ui->controller, "Vanilla Extract", "Flavor Essence Ltd.", 30, 20250701);
    addMaterialService(ui->controller, "Cocoa Powder", "ChocoGoods Suppliers", 150, 20250622);
    addMaterialService(ui->controller, "Almonds", "NutriNut Wholesalers", 120, 20250512);

    runUi(ui);


    freeUndoRedoStack(&controller->undoStack);
    freeUndoRedoStack(&controller->redoStack);
    destroyRepository(repo);
    free(controller);
    free(ui);
    
    return 0;
}