#include "ui.h"
#include "controller.h"
#include "repository.h"
#include <stdio.h>
#include <string.h>


void printMenu(){
    printf("\n1. Add material\n");
    printf("2. Remove material\n");
    printf("3. Update material\n");
    printf("4. See all expired materials containing your input\n");
    printf("5. Display all materials from a given supplier with the quantity lower than your input in descending order\n");
    printf("6. BONUS: See all non-expired materials containing your input\n");
    printf("7. Undo\n");
    printf("8. Redo\n");
    printf("0. Exit\n");
}

void runUi(Ui *ui){
    int userChoice;

    while(1){
        printMenu();
        printf("Enter your choice: ");
        if(scanf("%d", &userChoice) != 1){
            printf("\nInvalid input\n");
            while(getchar() != '\n');
            continue;
        }
        if(userChoice == 1){
            char name[30], supplier[30];
            int quantity, expirationDate;
            printf("Enter name: ");
            scanf("%s", name);

            printf("Enter supplier: ");
            scanf("%s", supplier);

            printf("Enter quantity: ");

            if(scanf("%d", &quantity) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }

            printf("Enter expirationDate : ");
            
            if(scanf("%d", &expirationDate) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }

            addMaterialService(ui->controller, name, supplier, quantity, expirationDate);
        }
        else if(userChoice == 2){
            char name[30], supplier[30];
            int expirationDate;
            printf("Enter the name of the material to remove: ");
            scanf("%s", name);

            printf("Enter the supplier of the material to remove: ");
            scanf("%s", supplier);

            printf("Enter the expiration date of the material to remove: ");
            if(scanf("%d", &expirationDate) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }

            removeMaterialService(ui->controller, name, supplier, expirationDate);


        }
        else if(userChoice == 3){
            char name[40], supplier[40];
            int newQuantity, expirationDate;

            printf("Enter the name of the material: ");
            scanf("%s", name);

            printf("Enter the supplier of the material: ");
            scanf("%s", supplier);

            printf("Enter the expiration date of the material: ");
            if(scanf("%d", &expirationDate) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }

            printf("Enter the new quantity: ");
            if(scanf("%d", &newQuantity) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }


            updateMaterialService(ui->controller,name, supplier, expirationDate, newQuantity);

        }
        else if(userChoice == 5){

            char userString[200];
            printf("Enter the supplier: ");
            scanf("%s", userString);

            
            int userQuantity;
            printf("Enter quantity: ");
            if(scanf("%d", &userQuantity) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }

            Repository *temp;
            temp = createRepository();

            for(int i = 0; i < ui->controller->repo->size; ++i){
                    if(strcmp(ui->controller->repo->materials[i].supplier, userString) == 0 && 
                        ui->controller->repo->materials[i].quantity < userQuantity){
                        temp->materials[temp->size++] = ui->controller->repo->materials[i];
                    }
                }
            
            int sortingOption;
            printf("\n1. Descending sort.\n");
            printf("2. Ascending sort.\n");

            if(scanf("%d", &sortingOption) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }
            if(sortingOption == 1){
                for(int i = 0; i < temp->size; ++i){
                    for(int j = 0; j < temp->size - 1; ++j){
                        if(temp->materials[j].quantity < temp->materials[j + 1].quantity){
                            Material aux;
                            aux = temp->materials[j];
                            temp->materials[j] = temp->materials[j + 1];
                            temp->materials[j + 1] = aux;
                        }
                    }
                }
            }
            else if(sortingOption == 2){
                for(int i = 0; i < temp->size; ++i){
                    for(int j = 0; j < temp->size - 1; ++j){
                        if(temp->materials[j].quantity > temp->materials[j + 1].quantity){
                            Material aux;
                            aux = temp->materials[j];
                            temp->materials[j] = temp->materials[j + 1];
                            temp->materials[j + 1] = aux;
                        }
                    }
                }
            }
            
            else{
                printf("Your choice should be 1 or 2! ");
                continue;
            }


            for(int i = 0; i < temp->size; ++i){
                printf("Name: %s; Supplier: %s; Quantity: %d; Expiration date: %d\n",
                        temp->materials[i].name, 
                        temp->materials[i].supplier,
                        temp->materials[i].quantity,
                        temp->materials[i].expirationDate);
            }
        }
        
        else if(userChoice == 4){
            int dateOfToday;
            printf("Enter today's date (YYYYMMDD): ");
            if(scanf("%d", &dateOfToday) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }
            getchar();

            char givenString[30];
            printf("\nEnter string (leave empty to show all expired materials): ");
            fgets(givenString, sizeof(givenString), stdin);
            givenString[strcspn(givenString, "\n")] = '\0';


            Repository *repo = ui->controller->repo;
            int g = 0;
            for (int i = 0; i < repo->size; ++i) {
                if (repo->materials[i].expirationDate < dateOfToday &&
                    (strlen(givenString) == 0 || strstr(repo->materials[i].name, givenString) != NULL)) {
                    printf("Name: %s; Supplier: %s; Expiration date: %d\n",
                        repo->materials[i].name, repo->materials[i].supplier,
                        repo->materials[i].expirationDate);
                        g = 1;
                }
            }

            if(!g){
                printf("All materials are not expired");
            }
        }

        else if(userChoice == 6){
            int dateOfToday;
            printf("Enter today's date (YYYYMMDD): ");
            if(scanf("%d", &dateOfToday) != 1){
                printf("\nInvalid input. Please enter an integer.\n");
                while (getchar() != '\n');
                continue;
            }
            getchar();

            char givenString[30];
            printf("\nEnter string (leave empty to show all expired materials): ");
            fgets(givenString, sizeof(givenString), stdin);
            givenString[strcspn(givenString, "\n")] = '\0';


            Repository *repo = ui->controller->repo;
            int g = 0;
            for (int i = 0; i < repo->size; ++i) {
                if (repo->materials[i].expirationDate > dateOfToday &&
                    (strlen(givenString) == 0 || strstr(repo->materials[i].name, givenString) != NULL)) {
                    printf("Name: %s; Supplier: %s; Expiration date: %d\n",
                        repo->materials[i].name, repo->materials[i].supplier,
                        repo->materials[i].expirationDate);
                        g = 1;
                }
            }

            if(!g){
                printf("All materials are not expired");
            }
        }
        else if(userChoice == 7){
            undo(ui->controller);
        }
        else if(userChoice == 8){
            redo(ui->controller);
        }

        else if(userChoice == 0){
            break;
        }

        else{
            printf("Your choice should be a number between 0 and 7!");
        }
    }
}