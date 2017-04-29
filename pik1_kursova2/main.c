#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "cars.h"

#define ESC 27

int main() {
        int option = 0;
        Elem *head;

        while(option < 1 || option > 5) {
                //system("CLS");

                puts("\n\nChoose option[1-5]\n");
                puts("1. Add new car");
                puts("2. List cars by given brand");
                puts("3. Delete car by given id");
                puts("4. List cars by given brand which price is higher than the avarage car price from that brand");
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

        switch(option) {
        case 1:
                addNewItems();
                break;
        case 2:
                break;
        case 3:
                break;
        case 4:
                break;
        case 5:
                return 0;
        }

        return 0;
}
