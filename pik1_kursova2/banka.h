#ifndef BANKA_H
#define BANKA_H

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

int getMenuOption();
void freeElems();
bool isEmpty();
Client createNewClient();
void addNewElem(Client);
void getClientById();
void deleteClientById();
void listClients();
void loadData();
void saveData();

#endif
