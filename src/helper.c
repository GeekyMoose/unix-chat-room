// -----------------------------------------------------------------------------
/**
 * \file	helper.c
 * \author	Constantin MASSON
 * \date	June 19, 2016
 *
 * \brief	General helper
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "helper.h"

int is_valid_username(const char *name){
	if(name == NULL){ return FALSE; }
	size_t size = strlen(name);
	if(size < USER_MIN_SIZE || size > USER_MAX_SIZE){
		return FALSE;
	}
	return TRUE;
}
