// -----------------------------------------------------------------------------
/**
 * \file	commands.h
 * \author	Constantin MASSON
 * \date	June 19, 2016
 *
 * \brief	Client commands component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#ifndef UNIXPROJECT_COMMANDS_H
#define UNIXPROJECT_COMMANDS_H

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <inttypes.h>

#include "wunixlib/assets.h"

#include "client_data.h"
#include "helper.h"
#include "messaging.h"
#include "constants.h"
#include "client.h"


/**
 * \brief			Display one command prompt and wait for user cmd.
 * \details			Function block till user enter its command.
 *
 * \param client	Client owner of the command prompt
 */
void prompt_cmd(ClientData *client);

/**
 * \brief			Process a command line.
 * \details			String can be a simple message, a command, a whisper.
 *
 * \param client	Client who wrote the line
 * \param str		String to process
 */
void process_console_line(ClientData *client, char *str);


#endif



