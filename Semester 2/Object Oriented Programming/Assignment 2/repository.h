#pragma once
#include "domain.h"
#include <stdio.h>

typedef struct{
    Material *materials;
    int size;
} Repository;

Repository *createRepository();
void addMaterial(Repository *repo, char *name, char *supplier, int quantity, int expirationDate);
void removeMaterial(Repository *repo, char *name, char *supplier, int expirationDate);
void updateMaterial(Repository *repo, char *name, char *supplier, int expirationDate, int newQuantity);
void destroyRepository(Repository *repo);
Repository *copyRepository(Repository *repo);