/*
 * ----------------------------------------------------------------------------
 * Unix C project
 * General helper
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */

#include "helper.h"

int is_valid_username(const char *name){
	if(name == NULL){ return FALSE; }
	size_t size = strlen(name);
	if(size < USER_MIN_SIZE || size > USER_MAX_SIZE){
		return FALSE;
	}
	return TRUE;
}
