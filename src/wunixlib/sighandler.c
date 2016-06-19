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

/**
 * @brief			Set a handler function with a specific signal
 * @brief			sigNo must be a valid signal
 *
 * @param f			Callback function when sigNo appear
 * @param sigNo		Signal to link with function
 * @return			1 if successfully created, otherwise, return -1
 */
int sethandler(void(*f)(int), int sigNo){
	struct sigaction act;
	memset(&act, 0x00, sizeof(struct sigaction));
	act.sa_handler = f;
	if (-1==sigaction(sigNo, &act, NULL)){
		return -1;
	}
	return 1;
}
