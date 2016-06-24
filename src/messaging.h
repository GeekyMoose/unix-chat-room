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

#define MSG_DELIMITER ";;;"


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



