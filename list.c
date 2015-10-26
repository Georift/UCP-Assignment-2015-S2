/**
 * \file list.c
 * \brief Handles linked list functionality
 * \author Tim Cochrane (17766247)
 * @bug No known bugs.
 */
#include "list.h"


/**
 * \brief Converts a linked list into a dynamicly allocated array.
 *
 * The array pointer char* array[] should already be allocated
 * with a size = (sizeof(char**) * arrLen).
 *
 * @param head Head node of the linked list.
 * @param array Destination array pointer.
 * @param arrLen Count of elements inside array.
 * @return void
 */
void listToArray(Word* head, char* array[], int arrLen)
{
    Word* cur = head;
    int ii;

    /* for each of the elements
     * jump to the next node in the list
     * copy it into the array */
    for (ii = 0; ii < arrLen; ii++)
    {
        cur = cur->next;
        array[ii] = (char*)malloc(sizeof(char)*WORD_LEN);
        strcpy(array[ii], cur->word);
    }
}

/**
 * \brief Frees all the elements within a dynamically allocated array.
 *
 * @param array Array to be freed
 * @param arrLen Number of elements inside the array
 * @return void
 */
void freeWordArray(char* array[], int arrLen)
{
    int ii;
    for (ii = 0; ii < arrLen; ii++)
    {
        free(array[ii]);
    }
}


/**
 * \brief Frees the elements in a linked list before freeing the head.
 *
 * It is important that after this function is called the passed in pointer
 * is assigned null. If you try to refree the head without doing this it can
 * cause errors to be produced in valgrind.
 *
 * @param head Pointer to the head node of the linked list.
 * @return void
 */
void freeLinkedList(Word* head)
{
    Word* cur = head;
    Word* toFree;

    cur = cur->next;
    while (cur != NULL)
    {
        toFree = cur;
        cur = cur->next;
        free(toFree);
    }
    free(head);
}

