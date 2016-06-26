// -----------------------------------------------------------------------------
/**
 * \file	user.c
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	User component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "user.h"


int user_is_valid_name(const char *name){
	if(name == NULL){ return -1; }
	size_t size = strlen(name);
	return (size < USER_MIN_SIZE || size > USER_MAX_SIZE) ? -1 : 1;
}


// -----------------------------------------------------------------------------
// List function implementations
// -----------------------------------------------------------------------------

int user_match_name(void* user, void* name){
	User u = *(User*) user;
	name = (char*) name;
	if(strcmp(u.login, name) == 0){
		return 1;
	}
	return 0;
}

int user_display(void* user){
	if(user == NULL){
		fprintf(stdout, "User is null\n");
		return 1;
	}
	User u = *(User*) user;
	fprintf(stdout, "User login '%s' / socket '%d' \n", u.login, u.socket);
	return 1;
}
