/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Network / Socket management
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */

#include "network.h"

int accept_client(int socket){
	int client_socket;
	client_socket = TEMP_FAILURE_RETRY(accept(socket, NULL, NULL));
	if(client_socket == -1){
		LOG_MSG("accept");
		return -1;
	}
	return client_socket;
}

int make_socket(int domain, int type){
	int sock;
	sock = socket(domain, type, 0);
	if(sock < 0){
		LOG_MSG("socket");
		return -1;
	}
	return sock;
}

int create_server_tcp_socket(uint16_t port, int backlog){
	struct sockaddr_in addr;
	int sock;

	//Create socket
	sock = make_socket(PF_INET, SOCK_STREAM);
	if(sock < 0){
		return -1;
	}

	//Create address
	addr.sin_family			= AF_INET;
	addr.sin_port			= htons(port);
	addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	
	//Bind socket with create address
	if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		LOG_MSG("bind");
		return -1;
	}

	//Start listening on this socket
	if(listen(sock, backlog) < 0){
		LOG_MSG("listen");
		return -1;
	}
	return sock; //Return created socket
}

