#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#define ESC 27

typedef enum {true = 1,false = 0} bool;

typedef struct {
    char id[20];
    char name[50];
    float cash;
    int months;
} Client;

typedef struct Node Node;
struct Node {
    Client client;
    Node *next;
};

Node *head = NULL;

int getMenuOption() {
    int option = 0;

    while(option < 1 || option > 5) {
            //system("CLS");

            puts("\n\nChoose option[1-5]\n");
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

bool isIdUnique(char id[]) {
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
    int errorFlag = 0;

    do {
        fflush(stdin);
        if(errorFlag) {
            puts("Wrong input , press ENTER to try again  or ESC to exit");
            if(getch() == ESC) {
                    freeElems();
                    exit(0);
            }
        }
        errorFlag = 0;

        puts("\nEnter client ID:");
        if(!(scanf("%s", newClient.id)) || !isIdUnique(newClient.id)) {
            errorFlag = 1;
            continue;
        };

        puts("Enter client names:");
        if(!(scanf("%s", newClient.name))) {
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
    } while(errorFlag);

    return newClient;
}

void addNewElem() {
    Client client = createNewClient();
    Node *newNode = (Node *) malloc (sizeof(Node));
    newNode->client = client;
    newNode->next = head;
    head = newNode;
    printf("\nThe client is added successfully!\n");
}

void getClientById() {
    if(isEmpty()) {
        puts("There is no clients!\n");
    } else {
        char id[20];
        Node *curr = head;
        puts("Enter the ID:");
        scanf("%s", id);
        while(curr != NULL) {
            if(strcmp(id, curr->client.id) == 0) {
                printf("Client name: %s\n", curr->client.name);
                printf("Client amount: %f\n", curr->client.cash);
                break;
            }
            curr = curr->next;
        }
    }
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
                printf("Client removed successfully!");
                break;
            }

            prev = curr;
            curr = curr->next;
        }

        if(!foundClient) {
            puts("No matching client was found for the given ID");
        }
    }
}

void printElems() {
    Node* curr = head;

    while(curr != NULL) {
        printf("\n%s", curr->client.name);
        curr = curr->next;
    }
    printf("\n\n");
}

float getAvrAmount() {
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

void loadData() {
    FILE* fp = NULL;
    fp = fopen("data.bin", "rb");

    //if file exists and it is opened successfully
    if(fp != NULL) {
            while(1) {
                if(fread()) {
                    break;
                }

            }


        fclose(fp);
    }
}

void saveData() {
    FILE* fp = NULL;

    //fp = fopen("data.bin", "")


}

int main() {
    int option = 0;
    //loadData();
    while(1) {
        option = getMenuOption();

        switch(option) {
        case 1:
                addNewElem();
                break;
        case 2:
                getClientById();
                break;
        case 3:
                deleteClientById();
                break;
        case 4:
                listClients();
                break;
        default:
                freeElems();
                return 0;
        }
    }

    //getClientById();

    return 0;
}
