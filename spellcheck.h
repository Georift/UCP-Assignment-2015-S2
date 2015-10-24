#ifndef SPELLCHECK_H
#define SPELLCHECK_h

#include <stdlib.h>

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


int loadFile(Word* head, char* filename);
void listToArray(Word* head, char* array[], int arrLen);
void freeLinkedList(Word* head);
void freeWordArray(char* array[], int arrLen);
int decision(char* word, char* suggestion);
void writeFile(char* array[], int arrLen, char* filename);

#endif
