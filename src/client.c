/*
 * ----------------------------------------------------------------------------
 * Unix C project - Client
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

#include "wunixlib/assets.h"
#include "wunixlib/sighandler.h"
#include "wunixlib/network.h"


void connect_to_server(const char *address, const uint16_t port){
	int socket;
	fprintf(stdout, "Try to connect server (%s) at port %d...\n", address, port);
	socket = create_client_tcp_socket(address, port);
	if(socket < 0){
		fprintf(stderr, "Unable to connect to server\n");
		return;
	}
	fprintf(stdout, "Connection successfully done\n");
}

int main(int argc, char **argv){
	fprintf(stdout, "Start client\n");

	//Set handlers
	sethandler(SIG_IGN, SIGPIPE);

	//DEV: Temporary
	connect_to_server("localhost", 4242);

	fprintf(stdout, "Stop client\n");
	return EXIT_SUCCESS;
}
