// -----------------------------------------------------------------------------
/**
 * \file	messaging.c
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Message logic
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "messaging.h"


// -----------------------------------------------------------------------------
// Static function for server message execution
// -----------------------------------------------------------------------------
static int messaging_server_exec_connect(ServerData *server, const int socket, const char *user_name){
	//Check is valid name
	if(user_is_valid_name(user_name) != 1){
		fprintf(stderr, "Connect requested with invalid name: %s\n", user_name);
		messaging_send_error(socket, "Name is not valid.");
		return -1;
	}
	//Check name is not used
	if(user_is_used(&(server->list_users), user_name)){
		fprintf(stderr, "Connect requested but name already used: %s\n", user_name);
		messaging_send_error(socket, "Name is already used.");
		return -1;
	}
	//Add name in server
	User new_user;
	strcpy(new_user.login, user_name); //Pass the name in struct
	list_append(&(server->list_users), &new_user); //Add user in server list
	fprintf(stdout, "New user (%s) added in server\n", user_name);
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


// -----------------------------------------------------------------------------
// Send Functions
// -----------------------------------------------------------------------------

int messaging_send_connect(const int socket, const char *name){
	char *cmd		= "connect"MSG_DELIMITER; //Add delimiter at end
	char *buffer	= NULL;
	buffer = (char*)malloc(sizeof(char) * strlen(cmd) + strlen(name));
	//Check if malloc failed.
	if(buffer == NULL){
		fprintf(stderr, "[ERR] Internal error occured. Unable to malloc (%s:%d)\n", __FILE__, __LINE__);
		return -1;
	}
	//Create the message (Possible update: check if fct failed)
	strcpy(buffer, cmd);
	strcat(buffer, name);
	bulk_write(socket, buffer, strlen(buffer));
	free(buffer);
	return 1;
}

int messaging_send_error(const int socket, char *msg){
	char *cmd		= "error"MSG_DELIMITER;
	char *buffer	= NULL;
	buffer = (char*)malloc(sizeof(char) * strlen(msg));
	//Check if malloc failed.
	if(buffer == NULL){
		fprintf(stderr, "[ERR] Internal error occured. Unable to malloc (%s:%d)\n", __FILE__, __LINE__);
		return -1;
	}
	//Create the message (Possible update: check if fct failed)
	strcpy(buffer, cmd);
	strcat(buffer, msg);
	bulk_write(socket, buffer, strlen(buffer));
	return 1;
}
