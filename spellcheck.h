#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preferences.h"
#include "check.h"

#define FALSE 0
#define TRUE !FALSE

/* 50 + 1 for the null terminator */
#define WORD_LEN 51

/**
 *  * \brief Linked list node to hold words
 *   */
typedef struct Word {
    /** String for holding the actual word */
    char word[50];
    /** pointer to the next struct in the linked list */
    struct Word* next;
} Word;
/* TODO sort our struct */


int loadFile(Word* head, char* filename);
void listToArray(Word* head, char* array[], int arrLen);
void freeLinkedList(Word* head);
void freeWordArray(char* array[], int arrLen);
int decision(char* word, char* suggestion);
void writeFile(char* array[], int arrLen, char* filename);
int autoCorrect(char* word, char* suggestion);

#endif
