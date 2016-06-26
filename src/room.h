// -----------------------------------------------------------------------------
/**
 * \file	room.h
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Room component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#ifndef UNIXPROJECT_ROOM_H
#define UNIXPROJECT_ROOM_H

#include <stdio.h>
#include "constants.h"
#include "user.h"


// -----------------------------------------------------------------------------
// Structures
// -----------------------------------------------------------------------------

/**
 * \brief Define a room component.
 */
typedef struct _room{
	char name[ROOM_MAX_SIZE+1]; //+1 for '\0'
	Linkedlist list_users; //List user in this room
} Room;


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

/**
 * \brief		Initialize a room with default value.
 * \details		Room is set with empty list of user inside and empty name.
 * \warning		Throw assert error if null param.
 *
 * \param room	Room to initialize
 */
void room_init(Room *room);

/**
 * \brief		Check whether the given name is valid for a room
 * \details		Null name will return -1
 *
 * \param name	The name to test
 * \return		1 if valid, otherwise, return -1
 */
int room_is_valid_name(const char *name);

/**
 * \todo		Not implemented yet
 *
 * \brief	Send a message to all user in the char room.
 */
void room_broadcast_message(Room *room);

/**
 * \todo		Not implemented yet
 *
 * \brief		Add a user in the room.
 * \details		Can fail (Return -1) if user already in this room.
 * \warning		Throw assert error if null param.
 *
 * \param room	Room where to place user
 * \param user	User to add in the room
 * \return		1 if successfully added, otherwise, return -1
 */
int room_add_user(Room *room, User *user);

/**
 * \todo	Not implemented yet
 *
 * \brief		Remove user from room.
 * \details		Can fail (Return -1) if user is not in the room.
 * \warning		Throw assert error if null param.
 *
 * \param room	Room where to remove user
 * \param user	User to remove from room
 * \return		1 if successfully removed, otherwise, return -1
 */
int room_remove_user(Room *room, User *user);


#endif



