#ifndef KURSOVA2_H_
#define KURSOVA2_H_


void addNewItem();

typedef struct {
        char *id;
        char color[20];
        float volume;
        char brand[20];
        float price;

} Car;

struct Elem {
        Car val;
        struct Elem *next;
};

typedef struct Elem Elem;



#endif
