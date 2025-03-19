#include "domain.h"
#include <stdlib.h>

void destroyMaterial(Material *mat){
    free(mat->name);
    free(mat->supplier);
    free(mat);
}