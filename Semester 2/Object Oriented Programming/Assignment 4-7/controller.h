#pragma once
#include "repo.h"
#include "validator.h"
#include <fstream>
#include <string>

class Controller {
private:
    Repository repo;
    std::vector<TrenchCoat> basket;
    std::string fileType;

public:
    Controller(std::string& fileType) : fileType(fileType) {}

    void addService(std::string size, std::string colour, int quantity, int price, std::string photo);
    void removeService(std::string size, std::string colour);
    void updateService(std::string size, std::string colour, int newQuantity, int newPrice);
    std::vector<TrenchCoat>& getCoatsService();

    void addToBasket( TrenchCoat& coat);
    void saveBasketToFile() ;
    void openBasketFile() ;
};