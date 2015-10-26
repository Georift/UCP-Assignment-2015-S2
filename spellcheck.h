#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE !FALSE

/* 50 + 1 for the null terminator */
#define WORD_LEN 51

/**
 *  * \brief Linked list node to hold words
 *   
 *  All files will be copied into the linked list initally
 *  because it allows for a unknown number of elements to be
 *  added.
 *
 */
typedef struct Word {
    /** String for holding the actual word */
    char word[WORD_LEN];
    /** pointer to the next struct in the linked list */
    struct Word* next;
} Word;

/* local header files moved below Word typedef so all when anything
 * requiring Word is included the typedef is already defined. */
#include "settings.h"
#include "callback.h"
#include "check.h"
#include "file.h"

void listToArray(Word* head, char* array[], int arrLen);
void freeLinkedList(Word* head);
void freeWordArray(char* array[], int arrLen);

#endif
