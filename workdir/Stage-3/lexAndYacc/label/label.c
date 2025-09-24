#include "./label.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>  

label* labelHead = NULL;
label* labelTail = NULL;

label* createLabelNode(char labelName[], int address) {
    label* newNode = (label*)malloc(sizeof(label));
    if (!newNode) {
        printf("Error: memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->labelName, labelName, 19); 
    newNode->labelName[19] = '\0';             
    newNode->address = address;
    newNode->next = NULL;                     
    return newNode;
}

void insertLabel(char labelName[], int address) {
    
    if (searchLabel(labelName) != -1) {
        printf("Error: Duplicate label '%s'\n", labelName);
        exit(1);
    }

    label* newNode = createLabelNode(labelName, address);
    if (labelHead == NULL) {
        labelHead = labelTail = newNode;
        return;
    }
    labelTail->next = newNode;
    labelTail = newNode;
}

int searchLabel(char labelName[]) {
    label* temp = labelHead;
    while (temp) {
        if (strcmp(temp->labelName, labelName) == 0) {
            return temp->address;
        }
        temp = temp->next;
    }
    return -1;
}