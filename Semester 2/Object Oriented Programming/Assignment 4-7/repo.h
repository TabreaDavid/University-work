#include <string>
#include <vector>
#include "domain.h"
#pragma once


class Repository{
    private:
        std::vector<TrenchCoat> coats;
    public:
        Repository();
        void repoAdd(TrenchCoat coat);

        void repoRemove(std::string size, std::string colour);

        void repoUpdate(std::string size, std::string colour,int newPrice, int newQuantity);

        int repoLength();

        std::vector<TrenchCoat>& getCoats();

        void saveToFile();
};