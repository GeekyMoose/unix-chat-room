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
static void messaging_server_exec_connect(ServerData *server, User *user, const char *user_name){
	if(user_name == NULL){
		fprintf(stderr, "Connect requested with invalid name (NULL)\n");
		messaging_send_error(user->socket, MSG_ERR_CONNECT, "Name is not valid.");
		return;
	}
	strcpy(user->login, user_name);
	int errstatus = server_data_add_user(server, user);
	//If invalid name
	if(errstatus == -1){
		fprintf(stderr, "Connect requested with invalid name: %s\n", user_name);
		messaging_send_error(user->socket, MSG_ERR_CONNECT, "Name is not valid.");
		return;
	}
	//If user already in server
	else if(errstatus == -2){
		fprintf(stderr, "Connect requested but name already used: %s\n", user_name);
		messaging_send_error(user->socket, MSG_ERR_CONNECT,  "Name is already used.");
		return;
	}

	//Place user in default room and send registration confirmation
	fprintf(stdout, "New user (%s) added in server (Sending confirmation)\n", user_name);
	messaging_send_confirm(user->socket, MSG_CONF_REGISTER, "You have been successfully registered in server");
	Room *defaultRoom = list_get_where(&(server->list_rooms), ROOM_WELCOME_NAME, room_match_name);
	room_add_user(defaultRoom, user);
	fprintf(stdout, "Current user list:\n");
	list_iterate(&(server->list_users), user_display);
	return;
}

static void messaging_server_exec_open_room(ServerData *server, User *user, char *name){
	//Params must be not null
	if(user == NULL || name == NULL){
		fprintf(stderr, "[ERR] Invalid open message (NULL data)\n");
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "Invalid room name.");
		return;
	}

	//Try to add room and check error
	name = str_trim(name);
	int errstatus = server_data_add_room(server, user, name);
	//Invalid name
	if(errstatus == -1){
		fprintf(stderr, "Invalid open message: room name '%s'\n", name);
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "Invalid room name.");
		return;
	}
	//Room already used on server
	else if(errstatus == -2){
		fprintf(stderr, "Invalid open message: room name '%s' already used.\n", name);
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "Invalid room name: already used.");
		return;
	}
	//Malloc error
	else if(errstatus == 0){
		fprintf(stderr, "Unable to create room '%s': internal error (malloc).\n", name);
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "Sorry, we are unable to create the room.");
		return;
	}
	fprintf(stdout, "New room created: '%s' (Owner: '%s')\n", name, user->login);
	fprintf(stdout, "Current rooms:\n");
	list_iterate(&(server->list_rooms), room_display);
	messaging_send_confirm(user->socket, MSG_CONF_GENERAL, "Room successfully created");
}

static void messaging_server_exec_whisper(ServerData *server, User *user, char *receiver, char *msg){
	//Check valid message parameters (not null)
	if(user == NULL || receiver == NULL || msg == NULL){
		fprintf(stderr, "[ERR] Invalid whisper message (NULL data)\n");
		return;
	}

	//Message shouldn't be empty (Or just spaces)
	msg = str_trim(msg);
	if(strlen(msg) == 0){
		fprintf(stderr, "[ERR] Invalid whisper message (Empty message)\n");
		return;
	}

	//Recover the receiver from list of user (Send error if wrong)
	User *u = list_get_where(&(server->list_users), receiver, user_match_name);
	if(u == NULL){
		messaging_send_error(user->socket, MSG_ERR_UNKOWN_USER, "User doesn't exists");
		return;
	}

	//@TODO add mutex for writing in socket
	messaging_send_whisper(u->socket, user->login, receiver, msg);
}

static void messaging_server_exec_room_bdcast(ServerData *server, User *user, const char* msg){
	fprintf(stdout, "DEBUG: %s : '%s'\n", __FILE__, msg);
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
	//User connection
	if(strcmp(token, "connect") == 0){
		messaging_server_exec_connect(server, user, strtok(NULL, MSG_DELIMITER));
		return 1;
	}
	//User whipser
	else if(strcmp(token, "whisper") == 0){
		char *sender	= strtok(NULL, MSG_DELIMITER);
		char *receiver	= strtok(NULL, MSG_DELIMITER);
		char *msg		= strtok(NULL, MSG_DELIMITER);
		messaging_server_exec_whisper(server, user, receiver, msg);
		return 1;
	}
	//Create new room
	else if(strcmp(token, "open") == 0){
		char *name = strtok(NULL, MSG_DELIMITER);
		messaging_server_exec_open_room(server, user, name);
	}
	//Room broadcast message
	else if(strcmp(token, "bdcast") == 0){
		char *msg		= strtok(NULL, MSG_DELIMITER);
		messaging_server_exec_room_bdcast(server, user, msg);
	}
	return -1; //Means no message match
}


