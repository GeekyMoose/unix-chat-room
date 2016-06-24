// -----------------------------------------------------------------------------
/**
 * \file	client.h
 * \author	Constantin MASSON
 * \date	June 19, 2016
 *
 * \brief	Client component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#ifndef UNIXPROJECT_CLIENT_H
#define UNIXPROJECT_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "wunixlib/assets.h"
#include "wunixlib/sighandler.h"
#include "wunixlib/network.h"

#include "client_data.h"
#include "messaging_client.h"
#include "commands.h"


//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
int client_connect_to_server(ClientData *client, const char *address, const uint16_t port);

#endif




