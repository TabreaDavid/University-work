#include "repository.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Repository *createRepository() {
    /*
     Creates a new repository.
     It initializes the size to 0 and allocates memory for storing materials.
    */
    Repository *repo = (Repository *)malloc(sizeof(Repository));
    repo->size = 0;
    repo->materials = (Material *)calloc(200, sizeof(Material)); 
    return repo;
}

Repository *copyRepository(Repository *repo) {
    /*
    Makes a copy of a given repository.
     It duplicates all materials inside it and returns a new repository with the same data.
    */
    Repository *newRepo = createRepository();
    newRepo->size = repo->size;
    
    for (int i = 0; i < repo->size; i++) {
        newRepo->materials[i].name = strdup(repo->materials[i].name);
        newRepo->materials[i].supplier = strdup(repo->materials[i].supplier);
        newRepo->materials[i].quantity = repo->materials[i].quantity;
        newRepo->materials[i].expirationDate = repo->materials[i].expirationDate;
    }
    
    return newRepo;
}

typedef struct {
    Repository *states[100]; 
    int index; 
} UndoRedoStack;

void addMaterial(Repository *repo, char *name, char *supplier, int quantity, int expirationDate) {
    /*
     Adds a new material to the repository.
     It stores its name, supplier, quantity, and expiration date.
    */
    Material material;
    material.name = strdup(name);
    material.supplier = strdup(supplier);
    material.quantity = quantity;
    material.expirationDate = expirationDate;

    repo->materials[repo->size++] = material;
}

void removeMaterial(Repository *repo, char *name, char *supplier, int expirationDate) {
    /*
      Removes a material from the repository if it matches the given details.
     If the material is found, it is deleted and the remaining materials shift to fill the gap.
     If it's not found, an error message is printed.
    */
    printf("Removing: %s %s %d\n", name, supplier, expirationDate); 

    for(int i = 0; i < repo->size; ++i) {
        printf("Checking: %s %s %d\n", repo->materials[i].name, repo->materials[i].supplier, repo->materials[i].expirationDate);

        if(strcmp(repo->materials[i].name, name) == 0 
        && strcmp(repo->materials[i].supplier, supplier) == 0 
        && repo->materials[i].expirationDate == expirationDate) {

            free(repo->materials[i].name);
            free(repo->materials[i].supplier);

            for(int j = i; j < repo->size - 1; ++j) {
                repo->materials[j] = repo->materials[j + 1];
            }
            repo->size -= 1;
            return;
        }
    }

    printf("Material not found!\n"); 
}

void updateMaterial(Repository *repo, char *name, char *supplier, int expirationDate, int newQuantity) {
    /*
     Updates the quantity of a material if it exists in the repository.
     If the material is found, its quantity is updated to the new value.
    */
    for(int i = 0; i < repo->size; ++i) {
        if(strcmp(repo->materials[i].name, name) == 0 &&
            strcmp(repo->materials[i].supplier, supplier) == 0 &&
            expirationDate == repo->materials[i].expirationDate) {
                repo->materials[i].quantity = newQuantity;
                return;
        }
    }
}

void destroyRepository(Repository *repo) {
    /*
      Deletes a repository and frees up memory.
     It makes sure to free all materials before freeing the repository itself.
    */
    if (!repo) return;
    
    for (int i = 0; i < repo->size; ++i) {
        free(repo->materials[i].name);
        free(repo->materials[i].supplier);
    }
    free(repo->materials);
    free(repo);
}