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
#include "room.h"


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
	Linkedlist list_rooms;
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

/**
 * \brief		Check whether the given name is already used in the server
 *
 * \param list	List where to check.
 * \param name	User name
 * \return		1 if is already used yet in the list, otherwise, return 0
 */
int server_data_name_is_used(const Linkedlist *list, const char *name);

/**
 * \brief		Add a room in the server.
 * \details		Room shoudln't be in the server already.
 * \warning		Not Null parameters expected
 *
 * \param server	Server where to add room
 * \param user		User owner of this room
 * \param			Name to give for this room
 * \return			1 if successfully added, -1 if invalid name, -2 if already in server
 */
int server_data_add_room(ServerData *server, User *user, const char *name);

/**
 * \brief		Check whether the given name is already used by a room in server.
 *
 * \param list	List of rooms in server.
 * \param name	Name to check
 * \return		1 if is already used, otherwise, return 0
 */
int server_data_room_is_used(const Linkedlist *list, const char *name);


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



