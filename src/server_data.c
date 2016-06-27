// -----------------------------------------------------------------------------
/**
 * \file	server_data.c
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Data in the server component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "server_data.h"


void server_data_init(ServerData *data){
	assert(data != NULL);
	list_init(&(data->list_users), NULL);
	data->is_listening	= 0;
	data->is_working	= 1;
}

int server_data_add_user(ServerData *server, User *user){
	//Check is valid name
	if(user_is_valid_name(user->login) != 1){
		return -1;
	}
	//Check name is not used
	if(server_data_name_is_used(&(server->list_users), user->login) == 1){
		return -2;
	}
	//Add name in server
	list_append(&(server->list_users), user); //Add user in server list
	return 1;
}

int server_data_name_is_used(const Linkedlist *list, char *name){
	return list_contains_where(list, (void*)name, user_match_name);
}

int server_data_add_room(ServerData *server, User *user, char *name){
	fprintf(stdout, "DEBUG %s:%d: user(%s) , name(%s)\n", __FILE__, __LINE__, user->login, name);
	//Check valid name
	if(room_is_valid_name(name) == -1){
		return -1;
	}
	//Check name used in server
	if(server_data_room_is_used(&(server->list_rooms), name) == 1){
		return -2;
	}
	Room *room = room_create(user, name);
	if(room == NULL){
		return 0;
	}
	list_append(&(server->list_rooms), room);
	return 1;
}

int server_data_room_is_used(const Linkedlist *list, char *name){
	return list_contains_where(list, (void*)name, room_match_name);
}
