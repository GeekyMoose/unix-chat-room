/*
 * ----------------------------------------------------------------------------
 * Unix C project - Server
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

#include "wunixlib/network.h"

#define BACKLOG 10


void usage(char *name){
	fprintf(stdout, "USAGE: %s port\n", name);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	fprintf(stdout, "Start server");

	if(argc != 2){
		usage(argv[0]);
	}

	int sock;

	//Create the socket, bind it, start listening
	sock = create_server_tcp_socket(atoi(argv[1]), BACKLOG);
	if(sock < 0){
		fprintf(stderr, "Unable to start the server...\n");
		return EXIT_FAILURE;
	}

	fprintf(stdout, "Stop server");
	return EXIT_SUCCESS;
}
