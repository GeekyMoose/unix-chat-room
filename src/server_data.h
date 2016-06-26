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

#ifndef UNIXPROJECT_SERVER_DATA_H
#define UNIXPROJECT_SERVER_DATA_H

#include <signal.h>

#include "wunixlib/linkedlist.h"
#include "constants.h"
#include "user.h"


// -----------------------------------------------------------------------------
// Structures / Data
// -----------------------------------------------------------------------------

/**
 * \brief		Represents a server.
 * \details		Keep a list of all connected users and several data about
 * 				server status.
 */
typedef struct _server_data{
	volatile sig_atomic_t is_listening;
	volatile sig_atomic_t is_working;
	Linkedlist list_users; //List of connected users.
} ServerData;



// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

/**
 * \brief		Initialize the server data.
 * \details		Create empty list of user and set "not listening" state.
 */
void server_data_init(ServerData *server);

/**
 * \brief		Add the user in the server
 * \details		User shouldn't be in the server list already.
 * \warning		Not Null parameters expected
 *
 * \param server	Server where to add user
 * \param user		User to add in server
 * \return			1 if successfully added, -1 if invalid name, -2 if already in server
 */
int server_data_add_user(ServerData *server, User *user);


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
int server_data_user_match_name(void *user, void*name);

/**
 * \brief		Display one user data.
 * \details		Meant to be used as iterate function for list.
 * 				User can be null (Null will be displayed).
 *
 * \param user	Void pointer to user
 * \return		1
 */
int server_data_user_display(void* user);


#endif



