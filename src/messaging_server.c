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
	//name must be not null
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
	Room *defaultRoom = list_get_where(&(server->list_rooms), ROOM_WELCOME_NAME, room_match_name);
	if(defaultRoom == NULL){
		//TODO user should be removed from server
		fprintf(stderr, "[ERR] Unable to recover the default room for new user\n");
		messaging_send_error(user->socket, MSG_ERR_CONNECT,  "An error occured, please try again.");
		return;
	}
	fprintf(stdout, "New user (%s) added in server (Sending confirmation)\n", user_name);
	messaging_send_confirm(user->socket, MSG_CONF_REGISTER, "You have been successfully registered in server");
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

static void messaging_server_exec_enter_room(ServerData* server, User* user, char* name){
	//Params must be not null
	name = (name == NULL) ? NULL : str_trim(name);
	if(user == NULL || name == NULL || room_is_valid_name(name) != 1){
		fprintf(stderr, "[ERR] Invalid enter message\n");
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "Invalid room name.");
		return;
	}

	//To enter a room, user must be first in the default room (The one from connection)
	if(strcmp(user->room, ROOM_WELCOME_NAME) != 0){
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "You must leave your current room first.");
		return;
	}

	//Check whether the requested room exists
	//TODO Add mutex on the room list
	Room* new_room = list_get_where(&(server->list_rooms), (void*)name, room_match_name);
	Room* old_room = list_get_where(&(server->list_rooms), (void*)user->room, room_match_name);
	if(new_room == NULL || old_room == NULL){
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "Room doesn't exists...");
		return;
	}

	//Change user room
	room_remove_user(old_room, user);
	room_add_user(new_room, user);
	messaging_send_confirm(user->socket, MSG_CONF_ROOM_ENTER, "You successfully enterred the room.");

	//TODO DEBUG
	fprintf(stdout, "\nDEBUG %s:%d - New data for list users:\n", __FILE__, __LINE__);
	list_iterate(&(server->list_users), user_display);
	fprintf(stdout, "DEBUG %s:%d - New data for list rooms:\n", __FILE__, __LINE__);
	list_iterate(&(server->list_rooms), room_display);
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
		messaging_send_error(user->socket, MSG_ERR_UNKOWN_USER, "User doesn't exists.");
		return;
	}

	//@TODO add mutex for writing in socket
	messaging_send_whisper(u->socket, user->login, receiver, msg);
}

static void messaging_server_exec_room_bdcast(ServerData *server, User *user, const char* msg){
	//Skipp invalid data
	if(user == NULL || msg == NULL){
		return;
	}

	//Recover room where user is
	Room* room = list_get_where(&(server->list_rooms), user->room, room_match_name);
	if(room == NULL){
		fprintf(stderr, "Unable to recover the room of user '%s'\n", user->login);
		messaging_send_error(user->socket, MSG_ERR_GENERAL, "Unable to send message in room.");
		return;
	}
	fprintf(stdout, "log room (%s): '%s' send '%s'\n", user->room, user->login, msg);
	room_broadcast_message(room, user, msg);
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
	//Enter rooom
	else if(strcmp(token, "enter") == 0){
		char *name = strtok(NULL, MSG_DELIMITER);
		messaging_server_exec_enter_room(server, user, name);
	}
	//Room broadcast message
	else if(strcmp(token, "bdcast") == 0){
		char *msg		= strtok(NULL, MSG_DELIMITER);
		messaging_server_exec_room_bdcast(server, user, msg);
	}
	return -1; //Means no message match
}


