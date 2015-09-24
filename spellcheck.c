/*
 *  UCP Assignment
 *  Tim Cochrane (17766247)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int maxCorrection;
    char dictionary[30];
    int autoCorrect;
} Settings;

typedef struct Word;
typedef struct {
    char word[50];
    Word* next;
};

int getSettings(Settings* inSet);

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


        if (fp == NULL)
        {
            /* display system error message */
            perror("Unable to open input file");
        }
        else
        {
            /* all good
             * Start reading into a linked list */
            /* do a test printing out sample.test */

            char readWord[51]; /* given max 50 chars + \0 */
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
                    /*printf("'%s'\n", readWord);*/
                }
            }while(eof != EOF);
        }

        fclose(fp);

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

int getSettings(Settings* inSet)
{
    FILE *fp = fopen("spellrc", "r");

    char name[14];
    char value[30];
    int eof;
    int status = 0;

    if (fp == NULL)
    {
        perror("Error opening spellrc");
        status = 1;
    }
    else
    {
        do
        {
            eof = fscanf(fp, "%s = %s", name, value);

            if (eof != EOF)
            {
                if (strcmp(name, "maxcorrection") == 0)
                {
                    (*inSet).maxCorrection = atoi(value);
                }
                else if (strcmp(name, "dictionary") == 0)
                {
                    strcpy((*inSet).dictionary, value);
                }
                else if (strcmp(name, "autocorrect") == 0)
                {
                    int result = -1;

                    if (strcmp(value, "yes") == 0)
                    {
                        result = 1;
                    }
                    else if (strcmp(value, "no") == 0)
                    {
                        result = 0;
                    }
                    else
                    {
                        printf("Unknown value '%s' for autocorrect.\n", value);
                        status = 1;
                        eof = EOF; /* to leave the loop */
                    }
                    (*inSet).autoCorrect = result;
                }
                else
                {
                    printf("Unknown variable '%s' in spellrc\n", name);
                    status = 1;
                    eof = EOF; /* to leave the loop */
                }
            }

        }while(eof != EOF);
        fclose(fp);
    }

    return status;
}
