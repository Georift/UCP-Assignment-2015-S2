/*
 *  UCP Assignment
 *  Tim Cochrane (17766247)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preferences.h"
#include "spellcheck.h"

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
            char** dictArray;
            char** userArray;

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
                Word* cur = dictHead;
                int ii;
                printf("Loaded %d words from %s\n", dictCount, 
                                            inSet->dictionary);

                /* start allocating an array for the dictionary file. */
                dictArray = (char**)malloc(sizeof(char*)*dictCount);

                /* for each element malloc it and add out word */
                for (ii = 0; ii < dictCount; ii++)
                {
                    cur = cur->next;
                    dictArray[ii] = (char*)malloc(sizeof(char)*51);
                    strcpy(dictArray[ii], cur->word);
                }

                userHead = (Word*)malloc(sizeof(Word));
                userCount = loadFile(userHead, argv[1]);

                /* ensure no error */
                if (userCount != -1)
                {
                    int jj;
                    cur = userHead;
                    printf("Loaded %d words from %s\n", userCount, argv[1]);

                    /* start allocating an array for the user file */ 
                    userArray = (char**)malloc(sizeof(char*)*userCount);

                    for (jj = 0; jj < userCount; jj++)
                    {
                        cur = cur->next;
                        userArray[jj] = (char*)malloc(sizeof(char)*51);
                        strcpy(userArray[jj], cur->word);
                    }

                }
                else
                {
                    /* an error occured during the loading of the user file */
                }
            }
            else
            {
               /* an error occured during the loading of the dictionary */

            } 

            

        }
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
