/*
 *  UCP Assignment
 *  Tim Cochrane (17766247)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preferences.h"
#include "spellcheck.h"

/* 50 + 1 for the null terminator */
#define WORD_LEN 51

/**
 * \brief Linked list node to hold words
 */
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

/**
 * \brief Starting point for the entire program.
 *
 * @param argc Count of parameters passed to the program + 1
 * @param argv Argument vector array containing all parameters
 * @return 1 when an error occurs. 0 for successful completion.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        /* incorrect usage */
        printf("Usage: %s [input file]\n", argv[0]);
    }
    else
    {
        Settings* inSet = (Settings*)malloc(sizeof(Settings**));

        if (getSettings(inSet) != 0)
        {
            /* using printf as opposed to perror as it can 
             * fail even if the file reads sucessfully */
            printf("Error loading/parsing spellrc.\n");
        }
        else
        {
            /* for storing our data in their inital
             * linked list form */
            Word* dictHead;
            int dictCount;
            Word* userHead;
            int userCount;

            /* for longer term storage of our data 
             * we will still make use of the previously
             * assigned xxxxCount variables */
            char** dictArray = NULL;
            char** userArray = NULL;

            /* have properly loaded the settings file
             * we can now continute with the spellcheck */
            #ifdef DEBUG
                printf("%d\n", inSet->maxCorrection);
                printf("%s\n", inSet->dictionary);
                printf("%d\n", inSet->autoCorrect);
            #endif

            /* loading in dictionary file */
            dictHead = (Word*)malloc(sizeof(Word));
            dictCount = loadFile(dictHead, inSet->dictionary);
            
            /* ensure no error */
            if (dictCount != -1)
            {
                printf("Loaded %d words from %s\n", dictCount, 
                                            inSet->dictionary);

                /* convert the linked list into a dynamically 
                 * allocated array */
                
                dictArray = (char**)malloc(sizeof(char*) * dictCount);
                listToArray(dictHead, dictArray, dictCount);
                /* now we are done with the linked list free it */
                freeLinkedList(dictHead);
                dictHead = NULL;

                /* free the array as we are no loner using it */
                freeWordArray(dictArray, dictCount);
                free(dictArray);
                dictArray = NULL;

                /*freeWordArray(dictArray, dictCount);*/
            }
            else
            {
                /* an error occured during the loading of the dictionary */
                printf("An error occured while loading the dictionary");
            } 

            /* load in the user file */
            userHead = (Word*)malloc(sizeof(Word));
            userCount = loadFile(userHead, argv[1]);

            /* ensure no error */
            if (userCount != -1)
            {
                printf("Loaded %d words from %s\n", userCount, argv[1]);

                /* convert the linked list into a dynamically
                 * allocated array */
                userArray = (char**)malloc(sizeof(char*) * userCount);
                listToArray(userHead, userArray, userCount);

                /* now we are done with the linked list free it */
                freeLinkedList(userHead);
                dictHead = NULL;

                /*freeWordArray(userArray, userCount);*/
                freeWordArray(userArray, userCount);
                free(userArray);
                userArray = NULL;
            }
            else
            {
                /* an error occured during the loading of the user file */
                printf("An error occured while loading the user file.");
            }

        }

        free(inSet);
    }
    return 0;
}

/*
 * will output -1 if failed to run correctly
 */
int loadFile(Word* head, char* filename)
{
    FILE* fp = fopen(filename, "r"); 
    int count = 0;

    if (fp == NULL)
    {
        /* give perror doesn't support similar formats
         * to printf. Make a string and concat filename */
        char errorStr[50] = "Unable to open file ";
        strcat(errorStr, filename);
        perror(errorStr);

        count = -1;
    }
    else
        
    {
        char readWord[51]; /* given max 50 chars + \0 */
        int eof;

        Word* cur; 
        cur = head; /* head will not contain any words */

        /* so we know how much to allocate later */
        count = 0;
        do
        {
            /* try reading the next word, fscanf will 
             * handle any amount of whitespace*/
            eof = fscanf(fp, "%s", readWord);

            /* only create the next node if valid read */
            if (eof != EOF)
            {
                /* allocate out next node in the list */
                cur->next = (Word*)malloc(sizeof(Word));
                cur = cur->next;

                /* make sure we have the end marker */
                cur->next = NULL;

                /* save our word */
                strcpy(cur->word, readWord);

                count++;
            }
        }while(eof != EOF);
        fclose(fp);

        #ifdef DEBUG
            /* print out the contents of the list */
            printf("DEBUG loadFile from %s\n", filename);
            cur = head;
            do
            {
                cur = cur->next;
                printf("'%s'\n", cur->word);
            }while (cur->next != NULL);
        #endif
    }

    return count;
}

/* given a link list head it will loop through
 * and place it into a dynmaically allocated array
 * the link list must contain atleast arrLen elements
 * and the dynamic array must be atleast arrLen long */
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


void freeWordArray(char* array[], int arrLen)
{
    int ii;
    for (ii = 0; ii < arrLen; ii++)
    {
        free(array[ii]);
    }
}

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
