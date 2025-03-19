#include "test.h"
#include <assert.h>
#include <string.h>

void testAddMaterial(Controller *controller) {
    addMaterialService(controller, "TestItem", "TestSupplier", 100, 20250101);
    assert(controller->repo->size == 1);
    assert(strcmp(controller->repo->materials[0].name, "TestItem") == 0);
    printf("testAddMaterial passed!\n");
}

void testRemoveMaterial(Controller *controller) {
    destroyRepository(controller->repo);
    controller->repo = createRepository();
    addMaterialService(controller, "Flour", "GrainCo Ltd.", 500, 20250715);
    removeMaterialService(controller, "Flour", "GrainCo Ltd.", 20250715);
    assert(controller->repo->size == 0);  
    printf("testRemoveMaterial passed!\n");
}

void testUpdateMaterial(Controller *controller) {
    addMaterialService(controller, "TestItem", "TestSupplier", 100, 20250101);
    updateMaterialService(controller, "TestItem", "TestSupplier", 20250101, 200);
    assert(controller->repo->materials[0].quantity == 200);
    printf("testUpdateMaterial passed!\n");
}