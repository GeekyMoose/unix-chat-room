// -----------------------------------------------------------------------------
/**
 * \file	server.h
 * \author	Constantin MASSON
 * \date	June 19, 2016
 *
 * \brief	Server component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#include "wunixlib/network.h"
#include "wunixlib/sighandler.h"
#include "wunixlib/assets.h"

#include "server_data.h"

/** \brief Max number of client possible in accept queue */
#define BACKLOG 10



/**
 * \brief			Start listening to new client.
 * \details			If server is already listening, do nothing.
 *
 * \param socket	Server socket where to listen
 */
void server_start_listening_clients(const int socket);

/**
 * \brief		Stop listening for new client.
 * \details		Do nothing if already not listening.
 */
void server_stop_listening_clients();
