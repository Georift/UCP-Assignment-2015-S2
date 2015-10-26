/**
 * \file spellcheck.h
 * \brief Forward declarations and various function includes
 * \author Tim Cochrane (17766247)
 */
#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \brief C 89 does not have boolean constants. */
#define FALSE 0
/** \brief C 89 does not have boolean constants. */
#define TRUE !FALSE

/* this must be the first of local headers as
 * the Word struct declared inside it is used everywhere. */
#include "list.h"

#include "settings.h"
#include "callback.h"
#include "check.h"
#include "file.h"

#endif
