#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ESC 27
#define true 1;
#define false 0;


int getMenuOption(void);
FILE* fileToRead(void);
FILE* fileToWrite(void);
void incrementCounters(char*, int*, int*);
void fileToFile(void);
void fileToStdin(void);
void stdinToFile(void);
void stdinToStdin(void);

int isMultiComment;
int isString;

int main() {
        int menu_option;
        while(1) {
                isMultiComment = false;
                isString = false;

                menu_option = getMenuOption();
                switch(menu_option) {
                case 1:
                        fileToFile();
                        break;

                case 2:
                        fileToStdin();
                        break;
                case 3:
                        stdinToFile();
                        break;

                case 4:
                        stdinToStdin();
                        break;

                case 5:
                        return 0;
                }
                puts("Press any key to continue...");
                getchar();
        }

        return 0;
}

int getMenuOption() {
        int option = 0;

        while(option < 1 || option > 5) {
                //system("CLS");

                puts("\n\nChoose option[1-5]\n");
                puts("1. Read from file and write to file");
                puts("2. Read from file and write to stdout");
                puts("3. Read from stdin and write to file");
                puts("4. Read from stdin and write to stdout");
                puts("5. Exit\n");

                int result = scanf("%d", &option);
                if(result == 0 || (option < 1 || option > 5)) {
                        puts("Wrong input, press ENTER to try again or ESC to exit");
                        fflush(stdin);

                        if(getch() == ESC) {
                                exit(0);
                        }
                }
        }
        return option;
}

FILE* fileToRead() {
        FILE* fp = NULL;
        char* fileName = NULL;
        int buff_size;
        char c;
        char* ext;

        do {
                c = '\0';
                buff_size = 1;
                if(fp != NULL) {
                        fclose(fp);
                }

                printf("\nWrite the input file name:\n");
                fflush(stdin);

                while((c = getchar()) != '\n') {
                        fileName = (char*) realloc (fileName, ++buff_size);
                        fileName[buff_size-2] = c;
                }
                fileName[buff_size-1] = '\0';

                fp = fopen(fileName, "r");
                ext = strrchr(fileName, '.');

                if((fp == NULL) || (ext == NULL) || (*(ext + 1) != 'c')) {
                        if(fp == NULL) {
                                puts("Error opening file");
                        } else if(ext == NULL) {
                                puts("The file doesn't have extension");
                        } else if(*(ext + 1) != 'c') {
                                puts("The file is not \".c\" file");
                        }
                        puts("Press ENTER to try again or ESC to exit");
                        if(getch() == ESC) {
                                if(fp != NULL) {
                                        fclose(fp);
                                }
                                free(fileName);
                                exit(0);
                        }
                }
        } while((fp == NULL) || (ext == NULL) || (*(ext + 1) != 'c'));

        free(fileName);

        return fp;
}

FILE* fileToWrite() {
        FILE* fp = NULL;
        char* fileName = NULL;
        int buff_size;
        char c;

        do {
                buff_size = 1;
                printf("\nWrite the output file name:\n");
                fflush(stdin);
                while((c = getchar()) != '\n') {
                        fileName = (char*) realloc (fileName, ++buff_size);
                        fileName[buff_size-2] = c;
                }
                fileName[buff_size-1] = '\0';
                fp = fopen(fileName, "w");
                if(fp == NULL) {
                        puts("Error opening file");
                        puts("Press ENTER to try again or ESC to exit");
                        if(getch() == ESC) {
                                free(fileName);
                                exit(0);
                        }
                }
        } while(fp == NULL);

        free(fileName);

        return fp;
}

void incrementCounters(char* line, int* identifierCount, int* assignmentOperatorCount) {
        int isIdentifier = false;
        int isSingleComment = false;
        int i;
        for(i = 0; i < strlen(line); i++) {
                if(!isSingleComment) {
                        if(line[i] == '\"' && !isMultiComment) {
                                if(i > 0) {
                                        if(line[i-1] != '\\') {
                                                if(!isString) {
                                                        isString = true;
                                                }
                                                else {
                                                        isString = false;
                                                }
                                        }
                                } else {
                                        if(!isString) {
                                                isString = true;

                                        } else {
                                                //check if string is enabled in previous line
                                                isString = false;
                                        }
                                }
                        }

                        if(i > 0 && !isString) {
                                if(line[i] == '/' && line[i-1] == '/') {
                                        isSingleComment = true;
                                }
                                if(line[i] == '*' && line[i-1] == '/') {
                                        isMultiComment = true;
                                }
                                if(line[i] == '/' && line[i-1] == '*') {
                                        isMultiComment = false;
                                }
                        }

                        if(!isMultiComment && !isString) {
                                if(line[i] == '=') {
                                        if(i > 0) {
                                                if(isIdentifier || line[i-1] == ' ') {
                                                        if(i < (strlen(line)-1)) {
                                                                if(line[i+1] != '=') {
                                                                        (*assignmentOperatorCount)++;
                                                                }
                                                        } else {
                                                                (*assignmentOperatorCount)++;
                                                        }
                                                }
                                        } else {
                                                if(i < (strlen(line)-1)) {
                                                        if(line[i+1] != '=') {
                                                                (*assignmentOperatorCount)++;
                                                        }
                                                } else {
                                                        (*assignmentOperatorCount)++;
                                                }
                                        }

                                }

                                if((((line[i] >= 'a' && line[i] <= 'z') || ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] == '_'))) && !isIdentifier)) {
                                        if(i > 0) {
                                                if(line[i-1] == ' ' || line[i-1] == '\t') {
                                                        (*identifierCount)++;
                                                        isIdentifier = true;
                                                }
                                        } else {
                                                (*identifierCount)++;
                                                isIdentifier = true;
                                        }
                                }

                                if(!((line[i] >= 'a' && line[i] <= 'z') || ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= '0' && line[i] <= '9') || line[i] == '_'))) {
                                        isIdentifier = false;
                                }
                        }
                }
        }
}

void fileToFile() {
        FILE* readFile = fileToRead();
        FILE* writeFile = fileToWrite();
        char line[81];
        int identifierCount = 0;
        int assignmentOperatorCount = 0;

        while (fgets(line, 80, readFile) != NULL) {
                incrementCounters(line, &identifierCount, &assignmentOperatorCount);
        }

        if(isString) {
                puts("\nError!, Open quotes left in file");
        } else {
                fprintf(writeFile, "Identifiers: %d\n", identifierCount);
                fprintf(writeFile, "Assignment operators: %d\n", assignmentOperatorCount);

                puts("\nSuccess!");
        }
        fclose(readFile);
        fclose(writeFile);
}

void fileToStdin() {
        FILE* readFile = fileToRead();
        char line[81];
        int identifierCount = 0;
        int assignmentOperatorCount = 0;

        while (fgets(line, 80, readFile) != NULL) {
                incrementCounters(line, &identifierCount, &assignmentOperatorCount);
        }

        if(isString) {
                puts("\nError!, Open quotes left in file");
        }
        else {
                printf("\nIdentifiers: %d\n", identifierCount);
                printf("Assignment operators: %d\n\n", assignmentOperatorCount);
        }

        fclose(readFile);
}

void stdinToFile() {
        FILE* writeFile = fileToWrite();
        char line[81];

        puts("\nWrite something:");
        fflush(stdin);
        while((fgets(line, 80, stdin) != NULL)) {
                fputs(line, writeFile);
        }

        puts("\nSuccess!");

        fclose(writeFile);
}

void stdinToStdin() {
        char** lines = NULL;
        int linesCount = 0;
        int i;

        puts("Write something:");

        fflush(stdin);
        do {
                lines = (char**) realloc (lines, ++linesCount * sizeof(char*));
                lines[linesCount-1] = (char*) malloc(81);

        } while(fgets(lines[linesCount-1], 80, stdin) != NULL);

        puts("\nOutput:");

        for(i = 0; i < linesCount; i++) {
                if(i < (linesCount - 1)) {
                        printf("%s", lines[i]);
                }
                free(lines[i]);
        }
        free(lines);
}
