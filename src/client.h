/*
 * ----------------------------------------------------------------------------
 * Unix C project - Client
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */

#ifndef UNIXPROJECT_CLIENT_H
#define UNIXPROJECT_CLIENT_H

#include <stdio.h>
#include <stdlib.h>

#include "wunixlib/assets.h"
#include "wunixlib/sighandler.h"
#include "wunixlib/network.h"

#include "commands.h"


//------------------------------------------------------------------------------
// Prototypes
//------------------------------------------------------------------------------
void connect_to_server(const char *address, const uint16_t port);

#endif


