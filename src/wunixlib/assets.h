/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Assets functions and macros
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */
#ifndef WUNIXLIB_ASSETS_H
#define WUNIXLIB_ASSETS_H


// ----------------------------------------------------------------------------
// Defines
// ----------------------------------------------------------------------------
#define TRUE 1
#define FALSE 0


// ----------------------------------------------------------------------------
// MACROS
// ----------------------------------------------------------------------------

//TEMP_FAILURE_RETRY MACRO
#define TEMP_FAILURE_RETRY(expression) \
		(__extension__ ({ long int __result; \
			do __result = (long int) (expression);\
			while (__result == -1L && errno == EINTR);\
		__result; }))

//Display log error message
#define LOG_ERR(source) \
		perror(source); \
		fprintf(stderr, "[ERR] file %s, line %d\n", __FILE__, __LINE__);

//Display log message
#define LOG_MSG(msg) \
	fprintf(stderr, "[ERR] file %s, line %d\n", __FILE__, __LINE__);


#endif



