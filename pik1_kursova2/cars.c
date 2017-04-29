#include <stdio.h>
#include <stdlib.h>

#include "cars.h"


void addNewItems() {
    char *id;
    char c;

    int id_index = 1;

    id = (char *) malloc (id_index * sizeof(char));

    puts("Enter car id: ");
    fflush(stdin);

    while((c = getchar()) != '\n') {
        if((c >= 'a' && c <= 'z') || ( c >='A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            id[id_index-1] = c;
            id = (char *) realloc (id, ++id_index * sizeof(char));
        }
    }
    id[id_index-1] = '\0';



    free(id);
}

void saveItems() {
    FILE *fp;

    fp = fopen("data.bin", "ab+");
    if(fp == NULL)
}
