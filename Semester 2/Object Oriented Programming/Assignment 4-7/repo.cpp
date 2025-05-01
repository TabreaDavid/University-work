#include "repo.h"
#include "exceptions.h"
#include <fstream>

Repository::Repository()
{
    std::ifstream inputFile("coats.txt");
    if(inputFile.is_open())
    {
        TrenchCoat coat;
        while (inputFile >> coat)
        {
            coats.push_back(coat);
        }
        inputFile.close();
    }
}
void Repository::repoAdd(TrenchCoat coat){
    for (auto c : coats)
    {
        if (c.getSize() == coat.getSize() && c.getColour() == coat.getColour())
        {
            throw RepositoryException("Coat already exists!");
        }
    }
    this->coats.push_back(coat);
    saveToFile();
}

void Repository::repoRemove(std::string size, std::string colour){
    for (auto it = coats.begin(); it < this->coats.end(); ++it)
    {
        if (it->getSize() == size && it->getColour() == colour)
        {
            this->coats.erase(it);
            saveToFile();
            return;
        }
    }
    throw RepositoryException("Coat does not exist!");
}

void Repository::repoUpdate(std::string size, std::string colour,int newPrice, int newQuantity)
{
    for (auto& c : coats)
    {
        if (c.getSize() == size && c.getColour() == colour)
        {
            c.setPrice(newPrice);
            c.setQuantity(newQuantity);
        }
    }
    saveToFile();
}

std::vector<TrenchCoat>& Repository::getCoats(){
    return this->coats;
}

void Repository::saveToFile()
{
    std::ofstream outputFile("coats.txt");
    if (outputFile.is_open())
    {
        for(auto c : coats)
        {
            outputFile << c << std::endl;
        }
        outputFile.close();
    } else {
        RepositoryException("File not open!");
    }
}