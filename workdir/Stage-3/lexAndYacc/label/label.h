#ifndef LABEL_H
#define LABEL_H

struct label{
    char labelName[20];
    int address;
    struct label* next;
};

typedef struct label label;

label* createLabelNode(char labName[], int address);
void insertLabel(char labelName[], int address);
int searchLabel(char labelName[]);

#endif