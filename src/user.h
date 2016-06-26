// -----------------------------------------------------------------------------
/**
 * \file	user.h
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	User component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#ifndef UNIXPROJECT_USER_H
#define UNIXPROJECT_USER_H

#include <stdio.h>
#include <string.h>
#include "wunixlib/linkedlist.h"
#include "constants.h"


// -----------------------------------------------------------------------------
// Structures
// -----------------------------------------------------------------------------

/**
 * \todo Not implemented yet
 *
 * \brief Define a user
 */
typedef struct _user{
	int socket;
	char login[USER_MAX_SIZE+1]; //+1 for '\0'
} User;


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

/**
 * \brief	Check whether the given name is valid.
 *
 * \param	Name to check if is valid
 * \return	1 if is valid, otherwise, return 0
 */
int user_is_valid_name(const char *name);


#endif



