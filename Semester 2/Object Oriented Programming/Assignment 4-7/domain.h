#include <string>
#include <iostream>
#pragma once

class TrenchCoat{
    private:
        std::string size;
        std::string colour;
        int price;
        int quantity;
        std::string photo;

    public:
        TrenchCoat(std::string size, std::string colour, int price, int quantity, std::string photo)
                        :size(size), colour(colour), price(price), quantity(quantity), photo(photo){}
        
        ~TrenchCoat() = default;

        TrenchCoat() = default;

        std::string getSize() const {return size;}
        void setSize(std::string newSize){ size = newSize;}

        std::string getColour() const {return colour;}
        void setColour(std::string newColour){ colour = newColour;}

        int getPrice() const {return price;}
        void setPrice(int newPrice){ price = newPrice;}

        int getQuantity() const {return quantity;}
        void setQuantity(int newQuantity){ quantity = newQuantity;}

        std::string getPhoto() const {return photo;}
        void setPhoto(std::string newPhoto){ photo = newPhoto;}

        friend std::ostream& operator<<(std::ostream& os, const TrenchCoat& coat)
        {
            os << coat.size << " " << coat.colour << " " << coat.price << " " << coat.quantity << " " << coat.photo;
            return os;
        }

        friend std::istream& operator>>(std::istream& is, TrenchCoat& coat)
        {
            is >> coat.size >> coat.colour >> coat.price >> coat.quantity >> coat.photo;
            return is;
        }

         std::string toCSV() const {
            return size + "," + colour + "," + std::to_string(price) + "," + std::to_string(quantity) + "," + photo;
        }

        std::string toHTML() const {
            return "<tr><td>" + size + "</td><td>" + colour + "</td><td>" + std::to_string(price) +
               "</td><td>" + std::to_string(quantity) + "</td><td><a href=\"" + photo + "\">Photo</a></td></tr>";
        }
};