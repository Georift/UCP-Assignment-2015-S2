#include <stdio.h>
#include <string.h>
#include "preferences.h"

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
