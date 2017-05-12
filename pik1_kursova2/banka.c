#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#include "banka.h"

//static - only in this file
static Node *head = NULL;

int getMenuOption() {
    int option = 0;

    while(option < 1 || option > 5) {
            //system("CLS");

            puts("\nChoose option[1-5]");
            puts("1. Add new client");
            puts("2. Get client by given id");
            puts("3. Delete client by given id");
            puts("4. List clients whoose amount is higher than the avarage one");
            puts("5. Exit\n");

            int result = scanf("%d", &option);
            if(result == 0 || (option < 1 || option > 5)) {
                    puts("Wrong input, press ENTER to try again or ESC to exit");
                    fflush(stdin);

                    if(getch() == ESC) {
                            return 0;
                    }
            }
    }

    return option;
}

void freeElems() {
    Node *curr = head;
    Node *temp;
    while(curr != NULL) {
        temp = curr->next;
        free(curr);
        curr = temp;
    }
}

bool isEmpty() {
    return head == NULL;
}

static bool isIdUnique(char id[]) {
    if(isEmpty()) return true;

    Node *curr = head;
    while(curr != NULL) {
        if(strcmp(id, curr->client.id) == 0) {
            return false;
        }
        curr = curr->next;
    }

    return true;
}

Client createNewClient() {
    Client newClient;
    bool errorFlag = 0;
    bool notUniqueIdFlag = 0;
    do {
        fflush(stdin);

        if(errorFlag || notUniqueIdFlag) {
            if(errorFlag) {
                puts("Wrong input, press ENTER to try again or ESC to exit");

            } else if(notUniqueIdFlag) {
                puts("This ID already exists, press ENTER to try again  or ESC to exit");
            }

            if(getch() == ESC) {
                    freeElems();
                    exit(0);
            }

            errorFlag = 0;
            notUniqueIdFlag = 0;
        }

        puts("\nEnter client ID:");
        if(!(scanf("%20[^\n]", newClient.id))) {
            errorFlag = 1;
            continue;
        } else if(!isIdUnique(newClient.id)) {
            notUniqueIdFlag = 1;
            continue;
        }

        fflush(stdin);
        puts("Enter client names:");
        if(!(scanf("%50[^\n]", newClient.name))) {
            errorFlag = 1;
            continue;
        };

        fflush(stdin);
        puts("Enter client amount:");
        if(!(scanf("%f", &newClient.cash))) {
            errorFlag = 1;
            continue;
        };

        puts("Enter client amount months:");
        if(!(scanf("%d", &newClient.months))) {
            errorFlag = 1;
        };
    } while(errorFlag || notUniqueIdFlag);

    puts("The client is added successfully!\n");
    puts("Press ENTER to Continue...");
    getch();
    return newClient;
}

void addNewElem(Client client) {
    Node *newNode = (Node *) malloc (sizeof(Node));
    newNode->client = client;
    newNode->next = head;
    head = newNode;
}

void getClientById() {
    if(isEmpty()) {
        puts("There is no clients!\n");
    } else {
        char id[20];
        bool foundClient = false;
        Node *curr = head;
        fflush(stdin);
        puts("Enter the ID:");
        scanf("%20[^\n]", id);

        while(curr != NULL) {
            if(strcmp(id, curr->client.id) == 0) {
                foundClient = true;
                printf("\nClient name: %s\n", curr->client.name);
                printf("Client amount: %f\n", curr->client.cash);
                break;
            }
            curr = curr->next;
        }
        if(!foundClient) {
            puts("No client with such ID");
        }
    }
    puts("Press ENTER to Continue...");
    getch();
}

void deleteClientById() {
    if(isEmpty()) {
        puts("There is no clients!\n");
    } else {
        char id[20];
        Node *curr = head;
        Node *prev = NULL;
        bool foundClient = false;

        puts("Enter the ID:");
        scanf("%s", id);

        while(curr != NULL) {
            if(strcmp(id, curr->client.id) == 0) {
                foundClient = true;
                if(prev == NULL && curr->next == NULL) {  //if there is only 1 client
                    head = NULL;
                } else if(prev == NULL) {
                    head = curr->next;
                } else {
                    prev->next = curr->next;
                }

                free(curr);
                puts("The client is removed successfully!");
                break;
            }

            prev = curr;
            curr = curr->next;
        }

        if(!foundClient) {
            puts("No matching client was found for the given ID");
        }
    }

    puts("Press ENTER to Continue...");
    getch();
}

static float getAvrAmount() {
    float sum = 0;
    int count = 0;
    Node *curr = head;

    while(curr != NULL) {
        sum += curr->client.cash;
        count++;
        curr = curr->next;
    }

    if(isEmpty()) {
        return 0;
    }

    return (float) (sum/count);
}

void listClients() {
    if(isEmpty()) {
        puts("There is no clients!\n");
    }
    else {
        float avarageAmount = getAvrAmount();
        Node *curr = head;

        while(curr != NULL) {
            if(curr->client.cash > avarageAmount) {
                printf("Client ID: \n%s\n", curr->client.id);
                printf("Client name: \n%s\n\n", curr->client.name);
            }
            curr = curr->next;
        }
    }
    puts("Press ENTER to Continue...");
    getch();
}

void loadData() {
    FILE* fp = NULL;
    Client client;

    fp = fopen("data.bin", "rb");
    //if file exists and it is opened successfully
    if(fp != NULL) {
            while(1) {
                if(fread(&client, sizeof(Client), 1, fp) != 1) {
                    break;
                }
                addNewElem(client);
            }

        fclose(fp);
    }
}

void saveData() {
    FILE* fp = NULL;

    fp = fopen("data.bin", "wb");
    if(fp == NULL) {
        puts("Error saving data!\n");
    } else {
        Node *curr = head;

        while(curr != NULL) {
            fwrite(&curr->client, sizeof(Client), 1, fp);
            curr = curr->next;
        }
        fclose(fp);
    }

}
