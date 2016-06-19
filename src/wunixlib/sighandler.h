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


//Prototypes
int sethandler(void(*f)(int), int sigNo);


#endif //End WUNIXLIB_SIGHANDLER_H


