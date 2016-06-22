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

#include <stdio.h>
#include <string.h>
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
	//TODO
	char login[USER_MAX_SIZE];
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


/**
 * \todo		Not implemented yet
 *
 * \brief		Send a whisper message to specific user.
 * \warning		Throw assert error if null param.
 *
 * \param sender	User who send the message
 * \param received	User who receive the message
 * \return			1 if successfully sent, otherwise, return -1
 */
int user_send_whisper_message(User *sender, User *receiver);
