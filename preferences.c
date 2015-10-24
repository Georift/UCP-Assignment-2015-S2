#include <stdio.h>
#include <string.h>
#include "preferences.h"
#include "spellcheck.h"

/**
 * \brief Handles the reading of spellrc file
 *
 * @param pointer to Settings struct for storing values
 * @return 1 if any errors occur. 0 for success
 */
int getSettings(Settings* inSet)
{
    FILE *fp = fopen("spellrc", "r");

    char name[14];
    char value[30];
    int eof;
    int status = 0;
    int ii;

    /* three ints represent if we have seen
     * each of the options.
     * [0] = maxCorrect
     * [1] = dict
     * [2] = autoCorrect */
    int assigned[3];

    if (fp == NULL)
    {
        perror("Error opening spellrc");
        status = 1;
    }
    else
    {
        do
        {
            /* we can only read a maximum of 29 chars as
             * dictionary will accept 30, 29 + \0 */
            eof = fscanf(fp, "%s = %29s", name, value);

            if (eof != EOF)
            {
                if (strcmp(name, "maxcorrection") == 0)
                {
                    assigned[0] = TRUE;
                    inSet->maxCorrection = atoi(value);
                }
                else if (strcmp(name, "dictionary") == 0)
                {
                    assigned[1] = TRUE;
                    strcpy(inSet->dictionary, value);
                }
                else if (strcmp(name, "autocorrect") == 0)
                {
                    int result = -1;

                    if (strcmp(value, "yes") == 0)
                    {
                        assigned[2] = TRUE;
                        result = 1;
                    }
                    else if (strcmp(value, "no") == 0)
                    {
                        assigned[2] = TRUE;
                        result = 0;
                    }
                    else
                    {
                        printf("Unknown value '%s' for autocorrect.\n", name);
                        status = 1;
                    }
                    inSet->autoCorrect = result;
                }
                else
                {
                    printf("Unknown variable '%s' in spellrc\n", name);
                    status = 1;
                }
            }

        }while(eof != EOF);
        fclose(fp);
    }

    for (ii = 0; ii < 3; ii++)
    {
        if (assigned[ii] != TRUE)
        {
            char missing[14];
            switch(ii)
            {
                case 0:
                    strcpy(missing, "maxcorrection");
                    break;
                case 1:
                    strcpy(missing, "dictionary");
                    break;
                case 2:
                    strcpy(missing, "autocorrect");
                    break;
            }
            status = 1;
            printf("Missing variable '%s' from spellrc.\n", missing);
        }
    }

    return status;
}
