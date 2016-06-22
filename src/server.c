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

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#include "wunixlib/network.h"
#include "wunixlib/sighandler.h"
#include "wunixlib/assets.h"

#define BACKLOG 10


volatile sig_atomic_t is_listening = FALSE;


void usage(char *name){
	fprintf(stdout, "USAGE: %s port\n", name);
	exit(EXIT_FAILURE);
}

void *client_handler(){
	fprintf(stdout, "New client accepted\n");
}

void start_listening_clients(const int socket){
	if(is_listening == TRUE){
		fprintf(stdout, "Server is already listening\n");
		return;
	}
	is_listening = TRUE;
	fprintf(stdout, "Server start listening new clients\n");
	int client_socket;
	pthread_t thread_id;
	while(is_listening == TRUE){
		fprintf(stdout, "Wait for client...\n");
		client_socket = accept_client(socket);
		pthread_create(&thread_id, NULL, client_handler, NULL);
		pthread_join(thread_id, NULL);
	}
}

void stop_listening_clients(){
	if(is_listening == FALSE){
		fprintf(stdout, "Server is already not listening\n");
		return;
	}
	fprintf(stdout, "Server stop listening for new clients\n");
	is_listening = FALSE;
}

void siginthandler(int sig){
	stop_listening_clients();
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
		fprintf(stderr, "Unable to start the server...\n");
		return EXIT_FAILURE;
	}

	//Start listening for new clients
	start_listening_clients(sock);

	//Close the socket
	if(TEMP_FAILURE_RETRY(close(sock)) < 0){
		return EXIT_FAILURE;
	}

	fprintf(stdout, "Server stop\n");
	return EXIT_SUCCESS;
}
