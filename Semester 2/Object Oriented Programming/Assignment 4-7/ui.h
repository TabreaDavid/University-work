#pragma once
#include "controller.h"

class Ui{
    private:
        Controller &controller;
    public:
        Ui(Controller& controller): controller(controller){};

        void runUi();
        
        void printMainMenu();

        void printAdminMenu();

        void printUserMenu();

        void adminMode();

        void userMode();
};

