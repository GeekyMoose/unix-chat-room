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
	if(user_is_used(&(server->list_users), user->login)){
		return -2;
	}
	//Add name in server
	list_append(&(server->list_users), user); //Add user in server list
	return 1;
}


// -----------------------------------------------------------------------------
// List function implementations
// -----------------------------------------------------------------------------

int server_data_user_match_name(void* user, void* name){
	User u = *(User*) user;
	name = (char*) name;
	if(strcmp(u.login, name) == 0){
		return 1;
	}
	return 0;
}

int server_data_user_display(void* user){
	if(user == NULL){
		fprintf(stdout, "User is null\n");
		return 1;
	}
	User u = *(User*) user;
	fprintf(stdout, "User login '%s' / socket '%d' \n", u.login, u.socket);
	return 1;
}
