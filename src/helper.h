/*
 * ----------------------------------------------------------------------------
 * Unix C project
 * General helper
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */

#ifndef UNIXPROJECT_HELPER_H
#define UNIXPROJECT_HELPER_H

#include <stdio.h>
#include <string.h>

#include "wunixlib/assets.h"

#include "constants.h"


//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------

/**
 * @brief		Check whether the given username fit the requirement
 *
 * @param name	User name to check
 * @return		TRUE if valid, otherwise, return FALSE
 */
int is_valid_username(const char *name);

#endif



