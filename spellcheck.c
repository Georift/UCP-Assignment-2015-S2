/**
 * @file spellcheck.c
 * @brief Starting point for the entire program.
 *
 * Usage: ./spellcheck [USER FILE]
 *
 * @author Tim Cochrane (17766247)
 * @bug No known bugs.
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
        
        /* getSettings will handel outputing any errors
         * that we need so we can do best case. */
        if (getSettings(inSet) == 0)
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
                /* output what we have stored for the spellrc */
                printf("DEBUG spellrc settings: \n");
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
                #ifdef DEBUG
                printf("Loaded %d words from %s\n", dictCount, 
                                            inSet->dictionary);
                #endif

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
                    #ifdef DEBUG
                    printf("Loaded %d words from %s\n", userCount, filename);
                    #endif

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
                    printf("An error occured while loading the user file\n");
                }
               
                /* free the array as we are no loner using it */
                freeWordArray(dictArray, dictCount);
                free(dictArray);
                dictArray = NULL;
            }
            else
            {
                /* an error occured during the loading of the dictionary */
                printf("An error occured while loading the dictionary\n");
            } 
        }
        free(inSet);
    }
    return 0;
}
