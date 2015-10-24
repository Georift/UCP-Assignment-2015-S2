/*
 *  UCP Assignment
 *  Tim Cochrane (17766247)
 */
#include "spellcheck.h"

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
        char filename[30];
        Settings* inSet = (Settings*)malloc(sizeof(Settings));
        
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

            strcpy(filename, argv[1]);

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
                userCount = loadFile(userHead, filename);

                /* ensure no error */
                if (userCount != -1)
                {
                    ActionFunc choice;
                    printf("Loaded %d words from %s\n", userCount, filename);

                    /* convert the linked list into a dynamically
                     * allocated array */
                    userArray = (char**)malloc(sizeof(char*) * userCount);
                    listToArray(userHead, userArray, userCount);

                    /* now we are done with the linked list free it */
                    freeLinkedList(userHead);
                    userHead = NULL;

                    /* this is where we want the check to call us
                     * we will change it depending on set autocorrect
                     * if autocorrect = yes then autoCorrect(..)
                     * if autocorrect = no  then decision(..) */
                    if (inSet->autoCorrect == TRUE)
                    {
                        choice = &autoCorrect;
                    }
                    else
                    {
                        choice = &decision;
                    }

                    /* do the actual checking */
                    check(userArray, userCount, dictArray, dictCount,
                            inSet->maxCorrection, choice);

                    /* now our userArray contains the corrected words */
                    remove(filename); /* remove file before writing */
                    writeFile(userArray, userCount, filename);


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
    /* we have autocorrect = no in spellrc
     * this means we have to ask to user if they
     * would like us to auto correct each word */

    /* assume that we don't correct */
    int doCorrection = 0;

    /* for looping until valid */
    int valid = FALSE;
    char answer;

    /* obviously we don't want the user to have to
     * pick between their word and NULL. */
    if (suggestion != NULL)
    {
        /* we aren't allowed to auto correct. Prompt */
        printf("Is the word '%s' meant to be '%s'? (y/n)", word, suggestion);
        while (valid == FALSE)
        {
            /* TODO maybe read as string then pull char to
             * to prevent dangeling chars */

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

/* this function will be called if in spellrc
 * autocorrect = yes. No logic just tell check()
 * we trust it's judgement. */
int autoCorrect(char* word, char* suggestion)
{
    return 1;
}

/* this function will output our word array to the filename
 * specified. It will only output words seperated by a space
 * as we are not required to preserve formatting */
void writeFile(char* array[], int arrLen, char* filename)
{
    FILE* fp = fopen(filename, "w");
    int ii;

    if (fp == NULL)
    {
        perror("Unable to write to input file");
    }
    else
    {
        /* for each element of our array output */
        for (ii = 0; ii < arrLen; ii++)
        {
            fprintf(fp, "%s\n", array[ii]);
        }

        fclose(fp);
    }
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
        /* given perror doesn't support similar formats
         * to printf. Make a string and concat filename */
        char errorStr[50] = "Unable to open file ";
        strcat(errorStr, filename);
        perror(errorStr);

        /* let the calling function know we failed */
        count = -1;
    }
    else
    {
        char readWord[WORD_LEN]; /* given max 50 chars + \0 */
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
