#include <stdio.h>

#include "banka.h"

int main() {
    int option = 0;
    loadData();

    while(1) {
        option = getMenuOption();

        switch(option) {
        case 1:
                addNewElem(createNewClient());
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
            if(!isEmpty()) {
                saveData();
                freeElems();
            }
                return 0;
        }
    }

    return 0;
}
