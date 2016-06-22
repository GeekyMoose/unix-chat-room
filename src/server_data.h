// -----------------------------------------------------------------------------
/**
 * \file	server_data.h
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Data in the server component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "wunixlib/linkedlist.h"


// -----------------------------------------------------------------------------
// Structures / Data
// -----------------------------------------------------------------------------

/**
 * \brief	List of all connected users
 * \details	Linkedlist
 */
Linkedlist list_users;


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

/**
 * \brief Initialize the server data.
 */
void init_server_data();

/**
 * \todo	Not implemented yet
 *
 * \brief
 */
int add_user_in_server(); //TODO
