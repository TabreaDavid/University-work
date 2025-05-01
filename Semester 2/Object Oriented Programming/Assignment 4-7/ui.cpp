#include "ui.h"
#include <iostream>
#include <string>
#include <cstdlib> 
#include "validator.h"
#include "domain.h"
using namespace std;

void clearInput() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}


int getaValidatedInt(){
    int value;
    while (true){
        cin >> value;
        if (cin.fail()){
            clearInput();
            cout << "\nInvalid input, please enter a valid integer: " ;
        }
        else{
            clearInput();
            return value;
        }
    }
}

void Ui::runUi(){
    int choice;

    while (1)
    {
        try
        {
            this->printMainMenu();
            cout << "\nEnter your choice: ";
            choice = getaValidatedInt();

            if (choice == 1)
                this->adminMode();

            else if (choice == 2)
                this->userMode();

            else if (choice == 0)
                break;

            else cout << "\nChoice is not on the menu!\n";
            
        }
        catch (RepositoryException& e)
        {
            cout << e.what() << '\n';
        }
        catch (ValidationException& e)
        {
            cout << e.what() << '\n';
        }

    }
}

void Ui::userMode() {
    int choice, basketSum = 0, buyingChoice;

    while (true) {
        this->printUserMenu();
        cout << "\nEnter your choice: ";
        choice = getaValidatedInt();

        if (choice == 1) {
            for (auto& c : this->controller.getCoatsService()) {
                cout << "\nSize: " << c.getSize()
                     << " | Colour: " << c.getColour()
                     << " | Price: " << c.getPrice()
                     << " | Quantity: " << c.getQuantity()
                     << " | Photo: " << c.getPhoto() << '\n';
                
                string photoURL = c.getPhoto();
                system(("open " + photoURL).c_str());

                cout << "1. Buy\n2. Pass";
                cout << "\nEnter choice: ";
                buyingChoice = getaValidatedInt();

                if (buyingChoice == 1) {
                    this->controller.addToBasket(c);   
                    basketSum += c.getPrice();
                    cout << "Item added. Total sum is: " << basketSum << "\n";
                } else if (buyingChoice != 2) {
                    cout << "\nInvalid choice. Skipping...\n";
                }
            }
        } else if (choice == 2) {
            cout << "\nThe total sum is: " << basketSum << endl;

            this->controller.saveBasketToFile();

        }
        else if (choice == 3) {
            this->controller.saveBasketToFile();  
            this->controller.openBasketFile();
        } else if (choice == 4) {
            break;

        } else {
            cout << "\nChoice not on the menu.\n";
        }
    }
}

void Ui::adminMode(){
    int choice;
    Validator validator;
    while (true)
    {       
            this->printAdminMenu();
            cout << "\nEnter your choice: ";
            choice = getaValidatedInt();

            if (choice == 1)
            {
                string photo, size, colour;
                int price, quantity;

                cout << "Enter size: ";
                cin >> size;

                cout << "Enter colour: ";
                cin >> colour;

                cout << "Enter price: ";
                price = getaValidatedInt();

                cout << "Enter quantity: ";
                quantity = getaValidatedInt(); 

                cout << "Enter photo: ";
                cin >> photo;

                TrenchCoat coat(size,colour,price,quantity,photo);
                validator.validate(coat);

                this->controller.addService(size, colour, price, quantity, photo);
            } else if (choice == 2)
                {
                    for (auto c : this->controller.getCoatsService())
                    {
                        cout << "Size: " << c.getSize() <<
                                " | Colour: " << c.getColour() <<
                                " | Price: " << c.getPrice() <<
                                " | Quantity: " << c.getQuantity() <<
                                " | Photo: " << c.getPhoto() << '\n';
                    }
            } else if (choice == 3)
                {
                string size, colour;
                int newQuantity, newPrice;

                cout << "Enter size: ";
                cin >> size;

                cout << "Enter colour: ";
                cin >> colour;

                cout << "Enter new quantity: ";
                newQuantity = getaValidatedInt();

                cout << "Enter new price: ";
                newPrice = getaValidatedInt();

                TrenchCoat coat(size,colour,newPrice,newQuantity," ");
                validator.validate(coat);

                this->controller.updateService(size, colour, newQuantity, newPrice);
            } else if (choice == 4)
                {
                string size, colour;
                cout << "Enter size: ";
                cin >> size;

                cout << "Enter colour: ";
                cin >> colour;

                this->controller.removeService(size, colour);
            } else if (choice == 5)
                break;

            else cout << "Choice not on the menu!";
    }
}

void Ui::printMainMenu()
{
    cout << "\nChoose mode: \n" << "1. Admin mode\n" << "2. User mode\n" << "0. Exit\n" ;
}

void Ui::printUserMenu()
{
    cout << "\n1. Enter buying mode\n" << "2. Check shopping basket cost\n" <<  "3. View saved basket\n" << "4. Back\n" ;
}

void Ui::printAdminMenu()
{
    cout << "\n1. Add coat\n" << "2. Display coats\n" << "3. Update coat\n" << "4. Remove coat\n" << "5. Back";
}