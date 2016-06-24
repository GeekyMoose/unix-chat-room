// -----------------------------------------------------------------------------
/**
 * \file	messaging.h
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Message logic
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#ifndef UNIXPROJECT_MESSAGING_H
#define UNIXPROJECT_MESSAGING_H

#include <stdio.h>
#include <string.h>

#include "wunixlib/stream.h"
#include "server_data.h"
#include "user.h"

#define MSG_DELIMITER ";;;"


// -----------------------------------------------------------------------------
// Receive process
// -----------------------------------------------------------------------------

/**
 * \brief			Process the given message in server side.
 * \details			Recover the type of message from the given msg and execute
 * 					the action for that kind of message.
 * 					NULL message return -1.
 * \note			This function is meant to be used by server side.
 * \warning			Message parameter will be altered and shouldn't be used anymore.
 * \warning			Server shouldn't be null.
 *
 * \param server	Server used
 * \param socket	The socket where message is from
 * \param msg		Message to process
 * \return			1 if successfully processed, otherwise, -1 (Unknown message)
 */
int messaging_exec_server_receive(ServerData *server, const int socket, char *msg);

/**
 * \todo		Not implemented yet
 *
 * \brief			Process the given message in client side.
 * \details			Recover the type of message from the given msg and execute
 * 					the action for that kind of message.
 * 					NULL message return -1.
 * \note			This function is meant to be used by client side.
 * \warning			Message parameter will be altered and shouldn't be used anymore.
 *
 * \param socket	The socket where message is from
 * \param msg		Message to process
 * \return			1 if successfully processed, otherwise, -1 (Unknown message)
 */
int messaging_exec_client_receive(const int socket, const char *msg);


// -----------------------------------------------------------------------------
// Send functions
//
// I didn't write doc for these functions. The working process is simple:
// each function send to the given socket a specific message (With right format, 
// with the right delimiter etc).
// Each message send -1 if error, otherwise, 1
// -----------------------------------------------------------------------------

int messaging_send_connect(const int socket, const char *name);
int messaging_send_error(const int socket, char *msg);


#endif



