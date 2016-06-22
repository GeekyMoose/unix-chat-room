// -----------------------------------------------------------------------------
/**
 * \file	server.c
 * \author	Constantin MASSON
 * \date	June 19, 2016
 *
 * \brief	Server component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "server.h"

volatile sig_atomic_t is_listening = FALSE;


// -----------------------------------------------------------------------------
// Client management functions
// -----------------------------------------------------------------------------
void *client_handler(){
	fprintf(stdout, "New client accepted\n");
}

void server_start_listening_clients(const int socket){
	if(is_listening == TRUE){
		fprintf(stdout, "Server is already listening\n");
		return;
	}
	is_listening = TRUE;
	fprintf(stdout, "Server start listening new clients\n");
	pthread_t thread_id;
	while(is_listening == TRUE){
		fprintf(stdout, "Wait for client...\n");
		int client_socket = accept_client(socket); //accept new client
		pthread_create(&thread_id, NULL, client_handler, NULL);
		pthread_join(thread_id, NULL);
	}
}

void server_stop_listening_clients(){
	if(is_listening == FALSE){
		fprintf(stdout, "Server is already not listening\n");
		return;
	}
	fprintf(stdout, "Server stop listening for new clients\n");
	is_listening = FALSE;
}

static void siginthandler(int sig){
	server_stop_listening_clients();
}


// -----------------------------------------------------------------------------
// Start / Launch functions
// -----------------------------------------------------------------------------

static void usage(char *name){
	fprintf(stderr, "USAGE: %s port\n", name);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	fprintf(stdout, "Server start\n");

	//check parameters (Must be: port_number)
	if(argc != 2){
		usage(argv[0]);
	}

	//Init signal process
	sigset_t mask, oldmask;
	sethandler(SIG_IGN, SIGPIPE);
	//sethandler(siginthandler, SIGINT);
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	//sigprocmask(SIG_BLOCK, &mask, &oldmask);

	//Create the server socket, bind it, start listening
	int sock = create_server_tcp_socket(atoi(argv[1]), BACKLOG);
	if(sock < 0){
		fprintf(stderr, "Unable to start the server (Unable to create the socket)...\n");
		return EXIT_FAILURE;
	}

	//Initialize server data
	init_server_data();

	//Start listening for new clients
	server_start_listening_clients(sock);

	//Close the socket
	fprintf(stdout, "Server is closing. Close socket...\n");
	if(TEMP_FAILURE_RETRY(close(sock)) < 0){
		fprintf(stderr, "Error while closing the socket...\n");
		return EXIT_FAILURE;
	}

	fprintf(stdout, "Server is stopped\n");
	return EXIT_SUCCESS;
}
