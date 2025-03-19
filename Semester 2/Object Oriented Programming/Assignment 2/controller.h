#pragma once
#include "repository.h"

typedef struct {
    Repository *states[100]; 
    int index; 
} UndoRedoStack;

typedef struct {
    Repository *repo;
    UndoRedoStack undoStack;
    UndoRedoStack redoStack;
} Controller;

void saveState(UndoRedoStack *stack, Repository *repo);
void addMaterialService(Controller *controller, char *name, char *supplier, int quantity, int expirationDate);
void removeMaterialService(Controller *controller, char *name, char *supplier, int expirationDate);
void updateMaterialService(Controller *controller, char *name, char *supplier, int expirationDate, int newQuantity);
void undo(Controller *controller);
void redo(Controller *controller);
void freeUndoRedoStack(UndoRedoStack *stack);