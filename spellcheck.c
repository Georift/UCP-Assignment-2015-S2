/*
 *  UCP Assignment
 *  Tim Cochrane (17766247)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preferences.h"

/**
 * \brief Linked list node to hold words
 */
typedef struct Word {
    /** String for holding the actual word */
    char word[50];
    /** pointer to the next struct in the linked list */
    struct Word* next;
} Word;

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
        FILE* fp = fopen(argv[1], "r");
        Settings* inSet = (Settings*)malloc(sizeof(Settings**));

        if (getSettings(inSet) != 0)
        {
            /* using printf as opposed to perror as it can 
             * fail even if the file reads sucessfully */
            printf("Error loading/parsing spellrc.\n");
        }
        else
        {
            /* have properly loaded the settings file
             * we can now continute with the spellcheck */
            #ifdef DEBUG
                printf("%d\n", (*inSet).maxCorrection);
                printf("%s\n", (*inSet).dictionary);
                printf("%d\n", (*inSet).autoCorrect);
            #endif

            /* try loading in dictionary file */
            if (fp == NULL)
            {
                perror("Unable to open input file");
            }
            else
            {
                /* all good                           *
                 * Start reading into a linked list   *
                 * do a test printing out sample.test */

                char readWord[51]; /* given max 50 chars + \0 */
                int eof;

                Word* head = (Word*)malloc(sizeof(Word));
                Word* cur; 

                head->next = (Word*)malloc(sizeof(Word));
                cur = head->next;

                strcpy(cur->word, "test");

                cur = head;
                cur = head->next;

                do
                {
                    eof = fscanf(fp, "%s", readWord);

                    if (eof != EOF)
                    {
                        printf("'%s'\n", readWord);
                    }
                }while(eof != EOF);
                fclose(fp);
            }
        }
    }
    return 0;
}
