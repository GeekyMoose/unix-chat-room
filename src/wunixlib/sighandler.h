/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Signal management
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */
#ifndef WUNIXLIB_SIGHANDLER_H
#define WUNIXLIB_SIGHANDLER_H

#include <signal.h>
#include <string.h>


// ----------------------------------------------------------------------------
// Prototypes
// ----------------------------------------------------------------------------

/**
 * @brief			Set a handler function with a specific signal
 * @brief			sigNo must be a valid signal
 *
 * @param f			Callback function when sigNo appear
 * @param sigNo		Signal to link with function
 * @return			1 if successfully created, otherwise, return -1
 */
int sethandler(void(*f)(int), int sigNo);


#endif //End WUNIXLIB_SIGHANDLER_H


