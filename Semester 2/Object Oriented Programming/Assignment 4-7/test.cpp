#include "test.h"
#include "domain.h"
#include "repo.h"
#include <cassert>
#include <iostream>

void testTrenchCoat(){
    TrenchCoat coat("1", "2", 3, 4, "5");
    
    assert(coat.getSize() == "1");
    assert(coat.getColour() == "2");
    assert(coat.getPrice() == 3);
    assert(coat.getQuantity() == 4);
    assert(coat.getPhoto() == "5");

    coat.setSize("6");
    coat.setColour("7");
    coat.setPrice(8);
    coat.setQuantity(9);
    coat.setPhoto("10");

    assert(coat.getSize() == "6");
    assert(coat.getColour() == "7");
    assert(coat.getPrice() == 8);
    assert(coat.getQuantity() == 9);
    assert(coat.getPhoto() == "10");
    std::cout << "Domain tests have passed!\n";

}

void testRepository(){
    Repository repo;
    repo.repoAdd(TrenchCoat("1", "2", 3, 4, "5"));

    assert(repo.getCoats()[0].getSize() == "1");
    assert(repo.getCoats().size() == 1);
        

    repo.repoAdd(TrenchCoat("5", "6", 7, 8, "9"));
    assert(repo.getCoats().size() == 2);

    repo.repoUpdate("5", "6", 98, 99);
    assert(repo.getCoats()[repo.getCoats().size() -1].getPrice() == 98);
    assert(repo.getCoats()[repo.getCoats().size() -1].getQuantity() == 99);

    repo.repoRemove("5", "6");
    assert(repo.getCoats().size() == 1);

    repo.repoRemove("1", "2");
    std::cout << "Repository tests have passed!\n";
}

void runTests(){
    testRepository();
    testTrenchCoat();
}