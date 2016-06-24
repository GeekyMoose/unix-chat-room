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

#include "wunixlib/linkedlist.h"


// -----------------------------------------------------------------------------
// Structures / Data
// -----------------------------------------------------------------------------

typedef struct _server_data{
	Linkedlist list_users; //List of connected users.
} ServerData;



// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

/**
 * \brief Initialize the server data.
 */
void server_data_init(ServerData *server);

/**
 * \todo	Not implemented yet
 *
 * \brief
 */
int add_user_in_server(ServerData *server); //TODO


#endif



