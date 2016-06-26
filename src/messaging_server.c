// -----------------------------------------------------------------------------
/**
 * \file	messaging_server.c
 * \author	Constantin MASSON
 * \date	June 24, 2016
 *
 * \brief	Message logic / Server side only
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "messaging_server.h"


// -----------------------------------------------------------------------------
// Static function for server message execution
// -----------------------------------------------------------------------------
static int messaging_server_exec_connect(ServerData *server, const int socket, const char *user_name){
	User new_user;
	new_user.socket = socket;
	strcpy(new_user.login, user_name);
	int errstatus = server_data_add_user(server, &new_user);
	//If invalid name
	if(errstatus == -1){
		fprintf(stderr, "Connect requested with invalid name: %s\n", user_name);
		messaging_send_error(socket, MSG_ERR_CONNECT, "Name is not valid.");
		return -1;
	}
	//If user already in server
	else if(errstatus == -2){
		fprintf(stderr, "Connect requested but name already used: %s\n", user_name);
		messaging_send_error(socket, MSG_ERR_CONNECT,  "Name is already used.");
		return -1;
	}
	fprintf(stdout, "New user (%s) added in server\n", user_name);
	fprintf(stdout, "Send registration confirmation to %s user\n", user_name);
	messaging_send_confirm(socket);
	return 1;
}

static int messaging_server_exec_whiper(ServerData *server, char *sender, char *receiver, char *msg){
	//Check valid message parameters (not null)
	if(sender == NULL || receiver == NULL || msg == NULL){
		fprintf(stderr, "[ERR] Invalid whisper message (NULL data)\n");
		return -1;
	}

	//Message shouldn't be empty (Or just spaces)
	msg = str_trim(msg);
	if(strlen(msg) == 0){
		fprintf(stderr, "[ERR] Invalid whisper message (Empty message)\n");
		return -1;
	}

	//Recover the receiver from list of user (Send error if wrong)
	//TODO

	//@TODO add mutex for writing in socket
	fprintf(stdout, "DEBUG: Whiper received: '%s' '%s' '%s'\n", sender, receiver, msg);
}


// -----------------------------------------------------------------------------
// Receive process Functions
// -----------------------------------------------------------------------------

int messaging_exec_server_receive(ServerData *server, const int socket, char *msg){
	if(msg == NULL){ return -1; }

	//Recover the type of message (First element in msg, must be not NULL)
	char *token = strtok(msg, MSG_DELIMITER);
	if(token == NULL){ return -1; }

	//Process each possible message
	if(strcmp(token, "connect") == 0){
		messaging_server_exec_connect(server, socket, strtok(NULL, MSG_DELIMITER));
	}
	else if(strcmp(token, "whisper") == 0){
		char *sender	= strtok(NULL, MSG_DELIMITER);
		char *receiver	= strtok(NULL, MSG_DELIMITER);
		char *msg		= strtok(NULL, MSG_DELIMITER);
		messaging_server_exec_whiper(server, sender, receiver, msg);
	}
	return -1; //Means no message match
}


