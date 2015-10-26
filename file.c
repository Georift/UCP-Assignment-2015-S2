/**
 * \file file.c
 * \brief Contains functions relating to file operations.
 *
 * \author Tim Cochrane (17766247)
 * \bug No known bugs.
 */
#include "file.h"

/**
 * \brief Handle writting of user array to file.
 *
 * In the assignment specification we are told that the program
 * does not have to preserve file formatting. Thus this function
 * will simple delimit the words with spaces eg. " ".
 *
 * This function will write from the beginning, make sure the file
 * is removed before writing as if the output text is less than the
 * input you may find some left over chars at the end of the file.
 *
 * @param array The now corrected words array.
 * @param arrLen Count of words inside array.
 * @param filename String with output filename.
 * @return void
 */
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
            fprintf(fp, "%s ", array[ii]);
        }

        fclose(fp);
    }
}


/**
 * \brief Loads all the words in a file into a linked list.
 *
 * In the input file the words should be seperated by either some
 * form of whitespace or a new line character. Any permutation of
 * these characters is fine.
 *
 * @param head Linked List to add all found words too.
 * @param filename Name of file to be read from as String.
 * @return int Outputs -1 if failed to run. Otherwise the number
 *             of words read from the file.
 *
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
