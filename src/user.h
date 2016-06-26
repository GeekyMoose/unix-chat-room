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
// General Functions
// -----------------------------------------------------------------------------

/**
 * \brief	Check whether the given name is valid.
 *
 * \param	Name to check if is valid
 * \return	1 if is valid, otherwise, return 0
 */
int user_is_valid_name(const char *name);


// -----------------------------------------------------------------------------
// List function implementations
// -----------------------------------------------------------------------------

/**
 * \brief		Used for list.
 * \details		Check whether name given match user name from list.
 * \details		See wunixlib/Linkedlist documentation for further informations.
 *
 * \param user	User tested
 * \param name	Name to test
 * \return		1 if match, otherwise, return 0
 */
int user_match_name(void* user, void* name);

/**
 * \brief		Display one user data.
 * \details		Meant to be used as iterate function for list.
 * 				User can be null (Null will be displayed).
 *
 * \param user	Void pointer to user
 * \return		1
 */
int user_display(void* user);

#endif



