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
static int messaging_server_exec_connect(ServerData *server, User *user, const char *user_name){
	strcpy(user->login, user_name);
	int errstatus = server_data_add_user(server, user);
	//If invalid name
	if(errstatus == -1){
		fprintf(stderr, "Connect requested with invalid name: %s\n", user_name);
		messaging_send_error(user->socket, MSG_ERR_CONNECT, "Name is not valid.");
		return -1;
	}
	//If user already in server
	else if(errstatus == -2){
		fprintf(stderr, "Connect requested but name already used: %s\n", user_name);
		messaging_send_error(user->socket, MSG_ERR_CONNECT,  "Name is already used.");
		return -1;
	}
	fprintf(stdout, "New user (%s) added in server (Sending confirmation)\n", user_name);
	fprintf(stdout, "Current user list:\n");
	list_iterate(&(server->list_users), server_data_user_display);
	messaging_send_confirm(user->socket);
	return 1;
}

static int messaging_server_exec_whisper(ServerData *server, User *user, char *receiver, char *msg){
	//Check valid message parameters (not null)
	if(user == NULL || receiver == NULL || msg == NULL){
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
	User *u = list_get_where(&(server->list_users), receiver, server_data_user_match_name);
	if(u == NULL){
		messaging_send_error(user->socket, MSG_ERR_UNKOWN_USER, "User doesn't exists");
		return -1;
	}

	//@TODO add mutex for writing in socket
	messaging_send_whisper(u->socket, user->login, receiver, msg);
}


// -----------------------------------------------------------------------------
// Receive process Functions
// -----------------------------------------------------------------------------

int messaging_server_exec_receive(ServerData *server, User *user, char *msg){
	if(msg == NULL){ return -1; }

	//Recover the type of message (First element in msg, must be not NULL)
	char *token = strtok(msg, MSG_DELIMITER);
	if(token == NULL){ return -1; }

	//Process each possible message
	if(strcmp(token, "connect") == 0){
		messaging_server_exec_connect(server, user, strtok(NULL, MSG_DELIMITER));
		return 1;
	}
	else if(strcmp(token, "whisper") == 0){
		char *sender	= strtok(NULL, MSG_DELIMITER);
		char *receiver	= strtok(NULL, MSG_DELIMITER);
		char *msg		= strtok(NULL, MSG_DELIMITER);
		messaging_server_exec_whisper(server, user, receiver, msg);
		return 1;
	}
	return -1; //Means no message match
}


