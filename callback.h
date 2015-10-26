/**
 * \file callback.h
 * \brief Function prototypes for callback functions.
 * \author Tim Cochrane (17766247)
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
