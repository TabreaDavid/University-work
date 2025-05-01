#include "controller.h"
#include "domain.h"

//Adds a coat to the repository
void Controller::addService(std::string size, std::string colour, int quantity, int price, std::string photo){
    this->repo.repoAdd(TrenchCoat(size, colour, price, quantity, photo));
}

//Removes a coat from the repository by size and colour
void Controller::removeService(std::string size, std::string colour){
    this->repo.repoRemove(size, colour);
}

//Updates a coat's price and quantity
void Controller::updateService(std::string size, std::string colour, int newQuantity, int newPrice){
    this->repo.repoUpdate(size, colour, newPrice, newQuantity);
}

void Controller::addToBasket( TrenchCoat& coat) {
    this->basket.push_back(coat);
}

//Returns all coats in the repository
std::vector<TrenchCoat>& Controller::getCoatsService(){
    return this->repo.getCoats();
}

//Saves current basket to a file of given type
void Controller::saveBasketToFile(){
    std::ofstream out;
    if (fileType == "csv") {
        out.open("basket.csv");
        for (auto& coat : basket)
            out << coat.toCSV() << "\n";
    } else {
        out.open("basket.html");
        out << "<!DOCTYPE html>\n";
        out << "<html>\n<body>\n<table border=\"1\">\n";
        out << "<tr>\n<th>\nSize</th>\n<th>Colour</th>\n<th>Price</th>\n<th>Quantity</th>\n<th>Photo</th>\n</tr>\n";
        for (auto& coat : basket)
            out << coat.toHTML() << "\n";
        out << "</table>\n</body>\n</html>\n";
    }
    out.close();
}

//Opens the basket in the correct app
void Controller::openBasketFile(){
    if (fileType == "csv")
        system("open basket.csv");
    else
        system("open basket.html");
}

