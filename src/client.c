// -----------------------------------------------------------------------------
/**
 * \file	client.c
 * \author	Constantin MASSON
 * \date	June 19, 2016
 *
 * \brief	Client component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "client.h"

volatile sig_atomic_t is_working = TRUE;

static void display_console(){
	fprintf(stdout, "Console.\n");
	while(is_working == TRUE){
		prompt_cmd();
	}
}

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

	//Start the console
	display_console();

	fprintf(stdout, "Stop client\n");
	return EXIT_SUCCESS;
}
