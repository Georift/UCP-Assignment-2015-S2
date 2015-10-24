/*
 *  UCP Assignment
 *  Tim Cochrane (17766247)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preferences.h"
#include "spellcheck.h"
#include "check.h"

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

/*typedef int (*ActionFunc)(char* word, char* suggestion);*/

int loadFile(Word* head, char* filename);
void listToArray(Word* head, char* array[], int arrLen);
void freeLinkedList(Word* head);
void freeWordArray(char* array[], int arrLen);
int decision(char* word, char* suggestion);

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
        Settings* inSet = NULL;
        inSet = (Settings*)malloc(sizeof(Settings**));

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

                /* load in the user file */
                userHead = (Word*)malloc(sizeof(Word));
                userCount = loadFile(userHead, argv[1]);

                /* ensure no error */
                if (userCount != -1)
                {
                    int ll = 0;
                    ActionFunc choice;
                    printf("Loaded %d words from %s\n", userCount, argv[1]);

                    /* convert the linked list into a dynamically
                     * allocated array */
                    userArray = (char**)malloc(sizeof(char*) * userCount);
                    listToArray(userHead, userArray, userCount);

                    /* now we are done with the linked list free it */
                    freeLinkedList(userHead);
                    userHead = NULL;

                    /* ALL IS WELL WE HAVE BOTH OUR ARRAYS */

                    /* this is where we want the callback */
                    choice = &decision;

                    check(userArray, userCount, dictArray, dictCount,
                            inSet->maxCorrection, choice);

                    #ifdef DEBUG
                        for (ll = 0; ll < userCount; ll++)
                        {
                            printf("'%s'\n", userArray[ll]);
                        }
                    #endif 

                    /* ALL THE WORK IS FINISHED START OUR CLEANUP */

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
               
                /* free the array as we are no loner using it */
                freeWordArray(dictArray, dictCount);
                free(dictArray);
                dictArray = NULL;
            }
            else
            {
                /* an error occured during the loading of the dictionary */
                printf("An error occured while loading the dictionary");
            } 
        }
        free(inSet);
    }
    return 0;
}

/* this is the callback function for check()
 * it will return true should he word be corrected
 * and false for words that shouldn't be corrected. */
int decision(char* word, char* suggestion)
{
    /* given the deffinition in the assignment specification
     * "number of single character edits required to transform
     * the word" I am assuming that these edits are simply mods
     * and not additions nor deletions. */

    /* assume that we don't correct */
    int doCorrection = 0;

    Settings* inSet = (Settings*)malloc(sizeof(Settings));
    getSettings(inSet);
    
    /* check if we are allowed to auto correct */
    if (inSet->autoCorrect == 1)
    {
        doCorrection = 1;
    }
    else
    {
        /* for looping until valid */
        int valid = FALSE;
        char answer;
        /* we aren't allowed to auto correct. Prompt */
        printf("Is the word '%s' meant to be '%s'? (y/n)", word, suggestion);
        while (valid == FALSE)
        {
            /* only taking chars */
            scanf("%c", &answer);

            /* although we wanted lower case for sake of usability
             * accept upper case characters as well */
            switch(answer)
            {
                case 'y': case 'Y':
                    doCorrection = 1;
                    valid = TRUE;
                    break;
                case 'n': case 'N':
                    doCorrection = 0;
                    valid = TRUE;
                    break;
                case '\n':
                    /* remove dangeling \n char */
                    break;
                default:
                    /* it will loop as valid remains false */
                    printf("Invalid input.\nPlease try again: ");
            }
        }
    }

    return doCorrection;
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
