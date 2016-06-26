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

int messaging_send_confirm(const int socket){
	char *cmd		= "confirm"MSG_DELIMITER; //Add delimiter at end
	char *buffer	= NULL;
	buffer = (char*)malloc(sizeof(char) * strlen(cmd));
	//Check if malloc failed.
	if(buffer == NULL){
		fprintf(stderr, "[ERR] Internal error occured. Unable to malloc (%s:%d)\n", __FILE__, __LINE__);
		return -1;
	}
	//Create the message (Possible update: check if fct failed)
	strcpy(buffer, cmd);
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
