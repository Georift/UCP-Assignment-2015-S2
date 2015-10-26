/**
 * \file callback.h
 * \brief Function prototypes for callback functions.
 * @bug No known bugs.
 */
#ifndef CALLBACK_H
#define CALLBACK_H

/* for TRUE/FALSE typedef */
#include "spellcheck.h"

/* for user prompt scanf/printf */
#include <stdio.h>

int decision(char* word, char* suggestion);
int autoCorrect(char* word, char* suggestion);

#endif
