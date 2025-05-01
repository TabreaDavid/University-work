#include "domain.h"
#include "controller.h"
#include <cstdio>
#include "repo.h"
#include "ui.h"
#include "test.h"

int main(){

    std::remove("coats.txt");
    std::remove("basket.html");
    std::remove("basket.csv");

    std::string fileType;

    while (1){
        std::cout << "Choose file type for shopping basket (csv/html) or 0 to exit: ";
        std::cin >> fileType;
        if (fileType == "0")
            return 0;
        else if (fileType != "html" and fileType != "csv")
                std::cout << "Wrong file type!\n";
        else
            break; 
    }
    runTests();

    Repository repo;
    Controller controller(fileType);

    controller.addService("M", "Black", 150.0, 5, "http://photo.com/black.jpg");
    controller.addService("L", "Blue", 180.0, 7, "http://photo.com/blue.jpg");
    controller.addService("S", "Red", 120.0, 3, "http://photo.com/red.jpg");
    controller.addService("XL", "Green", 200.0, 2, "http://photo.com/green.jpg");
    controller.addService("M", "Yellow", 140.0, 6, "http://photo.com/yellow.jpg");
    controller.addService("L", "White", 175.0, 8, "http://photo.com/white.jpg");
    controller.addService("S", "Pink", 130.0, 4, "http://photo.com/pink.jpg");
    controller.addService("XL", "Gray", 195.0, 5, "http://photo.com/gray.jpg");
    controller.addService("M", "Brown", 155.0, 9, "http://photo.com/brown.jpg");
    controller.addService("L", "Purple", 170.0, 7, "http://photo.com/purple.jpg");

    Ui ui(controller);
    ui.runUi();

}   
/*
# Assignment 06-07
## Week 8
* Implement at least requirements **1** and **2**.
## Week 9
* Implement all requirements
* Requirements **4** and **5** must be implemented using inheritance and polymorphism.

## Bonus possibility (0.2p, deadline week 9)
In addition to the file-based implementation for the repository, implement a true database-backed repository.
 For this, use inheritance and polymorphism. You are free to choose any type of database management system
  (e.g. `MySQL`, `SQLite`, `PostgreSQL`, `Couchbase` etc.).

## Problem Statement
For your solution to the previous assignment, add the following features:
1. Replace the templated DynamicVector with the STL vector. Use STL algorithms wherever possible in your 
application (e.g. in your filter function you could use `copy_if`, `count_if`). Replace all your for loops 
either with STL algorithms, or with C++11's range-based for loop.

2. Store repository data in a text file. When the program starts, entities are read from the file. Modifications\
 made during program execution are stored in the file. Implement this using the `iostream` library. 
 Create insertion and extraction operators for your entities and use these when reading/writing to files or the console.

3. Use exceptions to signal errors:
    - from the repository;
    - validation errors – validate your entities using Validator classes;
    - create your own exception classes.
    - validate program input.

4.	Depending on your assignment, store your (adoption list, movie watch list, shopping basket
 or tutorial watch list) in a file. When the application starts, the user should choose the type
  of file between `CSV` or `HTML`. Depending on the type, the application will save the list in
   the correct format.

    **Indications**\
    The CSV file will contain each entity on one line and the attributes will be separated by comma \
    The HTML file will contain a table, in which each row holds the data of one entity. The columns of the
     table will contain the names of the data attributes.\
    These are exemplified in the [example.csv](example.csv) and [example.html](example.html) files.
    `CSV` and `HTML` files are used to save and display data to the user; they act as program outputs, 
    so data should not be read from them!

5. Add a new command, allowing the user to see the:
    * adoption list
    * movie watch list
    * shopping basket
    * tutorial watch list\
Displaying the list means opening the saved file (`CSV` or `HTML`) with the correct 
application (`CSV` files using Notepad, Notepad++, Microsoft Excel etc. and `HTML` files using a browser)

6. Create a UML class diagram for your entire application. For this, 
you can use any tool that you like
 ([StarUML](https://staruml.io/), [LucidChart](https://www.lucidchart.com/ or [draw.io](https://app.diagrams.net/)) are only some examples. Many other options exist.
*/