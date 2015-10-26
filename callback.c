/**
 * \file callback.c
 * \brief Contains actionFunc callback functions
 * \author Tim Cochrane (17766247)
 * @bug No known bugs.
 */

#include "callback.h"

/**
 * \brief Prompt the user for a decision on suggested correction.
 *
 * @param word Pointer to a word identified as being misspelt.
 * @param suggestion Pointer to the word which check() found.
 * @return 1 if suggestion is accepted. 0 if no action should occur.
 */
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
            /* not actualy used. Just temp for holding
             * flushed char */
            char c;

            /* only taking chars */
            scanf("%c", &answer);

            /* to remove the dangeling characters from the input
             * buffer we can loop getchar to remove it all
             * source: c-faq.com/stdio/stdinflush2.html */
            while ( (c = getchar()) != '\n' && c != EOF)
            {
                /* do nothing we are just flushing buffer */
            }

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
                default:
                    /* it will loop as valid remains false */
                    printf("Invalid input.\nPlease try again: ");
            }
        }
    }
    return doCorrection;
}

/**
 * \brief Accepts any suggestion if suggestion is not null.
 *
 * The spellrc has allowed us to autocorrect every found misspelling.
 * Keep in mind sometimes check() can't find things and will call
 * this function with suggestion = null this is the only case we will
 * reject a suggestion.
 *
 * @param word Pointer to a word identified as being misspelt.
 * @param suggestion Pointer to a word which check() found.
 * @return 1 if suggestion is accepted. 0 if no action should occur.
 */
int autoCorrect(char* word, char* suggestion)
{
    int doCorrection = 0;

    if (suggestion != NULL)
    {
        doCorrection = 1;
    }
    return doCorrection;
}
