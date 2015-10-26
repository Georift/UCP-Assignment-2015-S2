/**
 * \file list.h
 * \brief Handles everything to do with linked lists.
 * \author Tim Cochrane (17766247)
 */
#ifndef LIST_H
#define LIST_H

/**
 * \brief Length of words that we are supporting
 *
 * Given that we must handle words of size 50 we must use
 * 51 to include room for the null terminator char '\0'
 */
#define WORD_LEN 51

/* malloc */
#include <stdlib.h>
/* strcpy */
#include <string.h>

/**
 *  * \brief Linked list node to hold words
 *
 *  All files will be copied into the linked list initally
 *  because it allows for a unknown number of elements to be
 *  added.
 *
 */
typedef struct Word {
    /** String for holding the actual word \see WORD_LEN*/
    char word[WORD_LEN];
    /** pointer to the next struct in the linked list */
    struct Word* next;
} Word;

void listToArray(Word* head, char* array[], int arrLen);
void freeLinkedList(Word* head);
void freeWordArray(char* array[], int arrLen);

#endif
