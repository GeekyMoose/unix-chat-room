// -----------------------------------------------------------------------------
/**
 * \file	messaging.h
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Message logic
 * \note	C Library for the Unix Programming Project
 *
 * \todo	An update can be done to regroup these functions a a generic one.
 * 			(The code inside is almost always the same, ... parameters
 * 			could be used instead in order to have only one function)
 */
// -----------------------------------------------------------------------------

#ifndef UNIXPROJECT_MESSAGING_H
#define UNIXPROJECT_MESSAGING_H

#include <stdio.h>
#include <string.h>
#include "wunixlib/stream.h"

#define MSG_DELIMITER ";;;"

// List of possible error value
#define MSG_ERR_CONNECT "msg_err_connect"
#define MSG_ERR_UNKOWN_USER "msg_err_unknown_user"
#define MSG_GENERAL_ERR "msg_general_err"

// -----------------------------------------------------------------------------
// Send functions
//
// I didn't write doc for these functions. The working process is simple:
// each function send to the given socket a specific message
// Message is formated using a defined format and delimiter etc.
// Each message send -1 if error, otherwise, 1
//
// Warning: atm, any parameter test is done and parameter should be valid (Not null etc)
// -----------------------------------------------------------------------------

int messaging_send_connect(const int socket, const char *name);
int messaging_send_confirm(const int socket, const char *msg);
int messaging_send_error(const int socket, char *type, char *msg);
int messaging_send_whisper(const int socket, const char *sender, const char *receiver, const char *msg);
int messaging_send_room_open(const int socket, const char *name);



#endif



