/*
 * ----------------------------------------------------------------------------
 * Unix C project
 * Manage client command line
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */

#ifndef UNIXPROJECT_COMMANDS_H
#define UNIXPROJECT_COMMANDS_H

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <inttypes.h>

#include "wunixlib/assets.h"
#include "helper.h"
#include "constants.h"


#define CMD_MAX_SIZE 255


/**
 * @brief		Process the received string from the console
 * @details		String can be a simple message, a command, a whisper.
 *
 * @param str	String to process
 */
void process_console_line(char *str);


#endif



