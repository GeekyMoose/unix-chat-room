/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Signal management
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */
#include "sighandler.h"


int sethandler(void(*f)(int), int sigNo){
	struct sigaction act;
	memset(&act, 0x00, sizeof(struct sigaction));
	act.sa_handler = f;
	if (-1==sigaction(sigNo, &act, NULL)){
		return -1;
	}
	return 1;
}
