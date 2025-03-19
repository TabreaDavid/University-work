#include "controller.h"
#include <stdio.h>

void addMaterialService(Controller *controller, char *name, char *supplier, int quantity, int expirationDate) {
    /*
    Adds a new material to the system.
     It also saves the current state before adding so the user can undo the action later.
    */
    saveState(&controller->undoStack, controller->repo);
    addMaterial(controller->repo, name, supplier, quantity, expirationDate);
}

void removeMaterialService(Controller *controller, char *name, char *supplier, int expirationDate) {
    /*
    Removes a material from the system.
     Before removing, it saves the current state so the action can be undone if needed.
    */
    saveState(&controller->undoStack, controller->repo);
    removeMaterial(controller->repo, name, supplier, expirationDate);
}

void updateMaterialService(Controller *controller, char *name, char *supplier, int expirationDate, int newQuantity) {
    /*
     Updates the quantity of a material.
     It saves the current state first so the update can be undone later.
    */
    saveState(&controller->undoStack, controller->repo);
    updateMaterial(controller->repo, name, supplier, expirationDate, newQuantity);
}

void saveState(UndoRedoStack *stack, Repository *repo) {
    /*
    Saves the current state of the repository into the undo/redo stack.
     If the stack is full, it prints an error message and doesn't save anything.
    */
    if (stack->index >= 100) {
        printf("Undo/Redo stack overflow!\n");
        return;
    }
    stack->states[stack->index++] = copyRepository(repo);
}

void freeUndoRedoStack(UndoRedoStack *stack) {
    /*
     Clears all saved states from the undo/redo stack.
     It also makes sure to free the memory used by those saved states.
    */
    for (int i = 0; i < stack->index; i++) {
        destroyRepository(stack->states[i]);
    }
    stack->index = 0;
}

void undo(Controller *controller) {
    /*
    Undoes the last change made to the repository.
     If there is at least one previous state, it restores it and saves the current state in the redo stack.
    */
    if (controller->undoStack.index > 0) {
        saveState(&controller->redoStack, controller->repo);
        destroyRepository(controller->repo);
        controller->repo = controller->undoStack.states[--controller->undoStack.index];
    }
}

void redo(Controller *controller) {
    /*
    Redoes the last undone change.
     If there's something to redo, it restores the state from the redo stack.
    */
    if (controller->redoStack.index > 0) {
        saveState(&controller->undoStack, controller->repo);
        destroyRepository(controller->repo);
        controller->repo = controller->redoStack.states[--controller->redoStack.index];
    }
}