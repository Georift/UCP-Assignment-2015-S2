/*
 *  UCP Assignment
 *  Tim Cochrane (17766247)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preferences.h"

/*typedef struct Word;
typedef struct {
    char word[50];
    Word* next;
};*/


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        /* incorrect usage */
        printf("Usage: %s [input file]\n", argv[0]);
    }
    else
    {
        /*FILE* fp = fopen(argv[1], "r");*/

        Settings* inSet = (Settings*)malloc(sizeof(Settings**));

        /*
        if (fp == NULL)
        {
            perror("Unable to open input file");
        }
        else
        {
            * all good
             * Start reading into a linked list *
           * do a test printing out sample.test *

            char readWord[51]; * given max 50 chars + \0 *
            int eof;

            Word* head = (Word*)malloc(sizeof(Word));
            Word* cur; 

            head->next = (Word*)malloc(sizeof(Word));
            cur = head->next;

            cur->word = "test";

            cur = head;
            cur = head->next;

            printf("%s", cur->word);

            do
            {
                eof = fscanf(fp, "%s", readWord);

                if (eof != EOF)
                {
                    *printf("'%s'\n", readWord);*
                }
            }while(eof != EOF);
        }

        fclose(fp);
        */
        if (getSettings(inSet) != 0)
        {
            perror("Error loading settings file.");
        }
        else
        {
            printf("%d\n", (*inSet).maxCorrection);
            printf("%s\n", (*inSet).dictionary);
            printf("%d\n", (*inSet).autoCorrect);

            /* try loading in dictionary file */
        }
    }

    return 0;
}
