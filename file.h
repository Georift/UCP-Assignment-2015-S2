/**
 * \file file.h
 * \brief Contains function prototypes for file operations.
 */
#ifndef FILE_H
#define FILE_H

/* perror + fprintf + fscanf */
#include <stdio.h>
/* strcpy */
#include <string.h>

/* for Word struct declaration */
#include "spellcheck.h"

int loadFile(Word* head, char* filename);
void writeFile(char* array[], int arrLen, char* filename);

#endif
