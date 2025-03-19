#pragma once
#include "controller.h"

typedef struct {
    Controller *controller;
}Ui;

void runUi(Ui *ui);
void printMenu();