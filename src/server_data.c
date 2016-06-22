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


void init_server_data(){
	list_init(&list_users, NULL);
}
