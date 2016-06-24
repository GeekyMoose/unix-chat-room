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


static void display_console(ClientData *client){
	fprintf(stdout, "Console.\n");
	while(client->is_working == TRUE){
		prompt_cmd(client);
	}
}

int client_connect_to_server(ClientData *client, const char *address, const uint16_t port){
	if(client->status == CONNECTED || client->status == CONNECTING){
		fprintf(stderr, "You are already connected!\n");
		return -1;
	}
	int socket;
	fprintf(stdout, "Try to connect server (%s) at port %d...\n", address, port);
	socket = create_client_tcp_socket(address, port);
	if(socket < 0){
		fprintf(stderr, "Unable to connect to server.\n");
		return -1;
	}
	client->status	= CONNECTING;
	client->socket	= socket;
	fprintf(stdout, "Connection successfully done.\n");
	return socket;
}

int main(int argc, char **argv){
	fprintf(stdout, "Start client\n");

	//Set handlers
	sethandler(SIG_IGN, SIGPIPE);

	//Create client data and start the console
	ClientData c;
	client_data_init(&c);
	display_console(&c);

	fprintf(stdout, "Stop client\n");
	return EXIT_SUCCESS;
}
