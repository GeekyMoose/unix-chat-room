// -----------------------------------------------------------------------------
/**
 * \file	messaging_client.c
 * \author	Constantin MASSON
 * \date	June 24, 2016
 *
 * \brief	Message logic / Client side only
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "messaging_client.h"


// -----------------------------------------------------------------------------
// Static function for server message execution
// -----------------------------------------------------------------------------
static int messaging_client_receiv_confirm(ClientData *client, const char *msg){
	client->status = CONNECTED; //TODO used only at the first confirm when registered
	fprintf(stdout, "\n%s\n", msg);
}

static int messaging_client_receiv_whisper(ClientData *client, char *sender, char *msg){
	fprintf(stdout, "\nwhisper [%s]: '%s'\n", sender, msg);
}

static int messaging_client_receiv_error(ClientData *client, char *type, char *msg){
	//MSG_ERR_CONNECT
	if(strcmp(type, MSG_ERR_CONNECT) == 0){
		fprintf(stderr, "\nUnable to connect: %s\n", msg);
		client->status = DISCONNECTED;
	}
	//DEFAULT
	else{
		fprintf(stderr, "\nError message: %s\n", msg);
	}
	return 1;
}


// -----------------------------------------------------------------------------
// Receive process Functions
// -----------------------------------------------------------------------------

int messaging_exec_client_receive(ClientData *client, const int socket, char *msg){
	if(msg == NULL){ return -1; }

	//Recover the type of message (First element in msg, must be not NULL)
	char *token = strtok(msg, MSG_DELIMITER);
	if(token == NULL){ return -1; }

	//Process each possible message
	if(strcmp(token,"confirm") == 0){
		messaging_client_receiv_confirm(client, strtok(NULL, MSG_DELIMITER));
	}
	else if(strcmp(token, "whisper") == 0){
		char *sender	= strtok(NULL, MSG_DELIMITER);
		char *receiver	= strtok(NULL, MSG_DELIMITER);
		char *msg		= strtok(NULL, MSG_DELIMITER);
		messaging_client_receiv_whisper(client, sender, msg);
	}
	else if(strcmp(token, "error") == 0){
		char *type	= strtok(NULL, MSG_DELIMITER);
		char *msg	= strtok(NULL, MSG_DELIMITER);
		messaging_client_receiv_error(client, type, msg);
	}
	return -1; //Means no message match
}

