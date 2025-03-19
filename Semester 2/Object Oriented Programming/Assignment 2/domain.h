#pragma once
#include <stdlib.h>

typedef struct{
    char *name;
    char *supplier;
    int quantity;
    int expirationDate;
} Material;

void destroyMaterial(Material *mat);