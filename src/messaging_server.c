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
		messaging_send_error(socket, "Name is not valid.");
		return -1;
	}
	//If user already in server
	else if(errstatus == -2){
		fprintf(stderr, "Connect requested but name already used: %s\n", user_name);
		messaging_send_error(socket, "Name is already used.");
		return -1;
	}
	fprintf(stdout, "New user (%s) added in server\n", user_name);
	fprintf(stdout, "Send registration confirmation to %s user\n", user_name);
	messaging_send_confirm(socket);
	return 1;
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
	if(strcmp(token,"connect") == 0){
		messaging_server_exec_connect(server, socket, strtok(NULL, MSG_DELIMITER));
	}
	return -1; //Means no message match
}


