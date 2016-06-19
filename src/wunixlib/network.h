/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Network / Socket management
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */

#ifndef WUNIXLIB_NETWORK_H
#define WUNIXLIB_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netdb.h>


//Display log message (For errors)
#define LOG_MSG(msg) \
		perror(msg); \
		fprintf(stderr, "[ERR] file %s, line %d\n", __FILE__, __LINE__);

//TEMP_FAILURE_RETRY MACRO
#define TEMP_FAILURE_RETRY(expression) \
		(__extension__ ({ long int __result; \
			do __result = (long int) (expression);\
			while (__result == -1L && errno == EINTR);\
		__result; }))



// ----------------------------------------------------------------------------
// Prototypes
// ----------------------------------------------------------------------------

/**
 * @brief			Accept new connection for given socket.
 *
 * @param socket	Socket where to apply accept
 * @return			The new socket connected
 */
int accept_client(int socket);

/**
 * @brief		Create a new socket.
 *
 * @param domain	Domain for the socket (AF_INET...)
 * @param type		Type of socket (SOCK_STREAM, SOCK_DGRAM...)
 * @return			The created socket or -1 if error
 */
int make_socket(int domain, int type);

/**
 * @brief			Create a new tcp server socket.
 * @details			Created connection is AD_INET at address INADDR_ANY.
 * 					The socket start listening as soon as it's created.
 *
 * @param port		Connection port for this socket
 * @param backlog	Listen backlog
 * @return			The socket value if created successfully, otherwise, return -1
 */
int create_server_tcp_socket(uint16_t port, int backlog);

#endif


