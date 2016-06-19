/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Stream management
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */
#ifndef WUNIXLIB_STREAM_H
#define WUNIXLIB_STREAM_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

//TEMP_FAILURE_RETRY MACRO
#define TEMP_FAILURE_RETRY(expression) \
		(__extension__ ({ long int __result; \
			do __result = (long int) (expression);\
			while (__result == -1L && errno == EINTR);\
		__result; }))



//Prototypes
int64_t bulk_read(int, char*, size_t);
int64_t bulk_write(int, char*, size_t);
int append_to_file(char *filename, char *buf, size_t len);


#endif //end WUNIXLIB_STREAM_H


