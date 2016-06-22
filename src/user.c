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
	if(size < USER_MIN_SIZE || size > USER_MAX_SIZE){
		return -1;
	}
	return 1;
}
