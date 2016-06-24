// -----------------------------------------------------------------------------
/**
 * \file	messaging_client.h
 * \author	Constantin MASSON
 * \date	June 24, 2016
 *
 * \brief	Message logic / Client side only
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#ifndef UNIXPROJECT_MESSAGING_CLIENT_H
#define UNIXPROJECT_MESSAGING_CLIENT_H

#include <stdio.h>
#include <string.h>

#include "wunixlib/stream.h"
#include "user.h"
#include "messaging.h"


// -----------------------------------------------------------------------------
// Receive process
// -----------------------------------------------------------------------------

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

#endif



