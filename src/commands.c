// -----------------------------------------------------------------------------
/**
 * \file	commands.c
 * \author	Constantin MASSON
 * \date	June 19, 2016
 *
 * \brief	Client commands component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "commands.h"


//------------------------------------------------------------------------------
// Static functions for each command process
//
// Each function process a specific command and execute the required action.
// In all case, str parameter is the command written by user without the command 
// name (For example, without !connect' for connection command)
//------------------------------------------------------------------------------

static void exec_connect(ClientData *client, char *str){
	//If first elt is '\0', means no param given. Show usage
	if(str[0] == '\0'){
		fprintf(stderr, "Invalid command. Usage: !connect <username>@<server> [:port]\n");
		return;
	}

	//Recover values from str
	char args[CMD_MAX_SIZE] = "";
	uint16_t port;
	sscanf(str, "%s %"SCNd16, args, &port); //port optional, 0 if not here
	char *token = NULL, *username = NULL, *servername = NULL;

	//Recover username and servername
	token		= strtok(args, "@");
	username	= token;
	servername	= strtok(NULL, "@");

	//Servername and username must be here
	if(username == NULL || servername == NULL){
		fprintf(stderr, "Invalid command. Usage: !connect <username>@<server> [:port]\n");
		return;
	}
	//If no port given, set to default
	if(port == 0 || port == 65535){
		port = PORT_DEFAULT; //65535 or 0 sounds to be set if no value in sscanf
	}

	//Connect and send name (Or return if unable to connect)
	int socket = client_connect_to_server(client, servername, port);
	if(socket == -1){ return; }
	fprintf(stdout, "Send name to server...\n");
	strcpy(client->login,username);
	messaging_send_connect(socket, username);
	//Warning, I had a bug if starting listening before the send_connect process.
	client_start_listening(client);
}


//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

static int is_command(const char *str){
	if(str == NULL){ return FALSE; }
	return str[0] == '!' ? TRUE : FALSE;
}

static int is_whisper(const char *str){
	if(str == NULL){ return FALSE; }
	return str[0] == '*' ? TRUE : FALSE;
}

static void process_command(ClientData *client, char *cmd){
	//Check whether command size is correct
	if(strlen(cmd) > CMD_MAX_SIZE){
		fprintf(stderr, "Command is to long.");
		return;
	}

	//Recover the command name
	cmd++; //Skip the '!' char
	char cmd_name[CMD_MAX_SIZE+1]; //+1 for '\0'
	sscanf(cmd, "%s", cmd_name);
	char *args = cmd+strlen(cmd_name); //args start just after the cmd name

	//Call function according to command received
	if(strcmp(cmd_name, "connect") == 0){
		exec_connect(client, args);
	}
	else if(strcmp(cmd_name, "bye") == 0){
	}
	else if(strcmp(cmd_name, "rooms") == 0){
	}
	else if(strcmp(cmd_name, "open") == 0){
	}
	else if(strcmp(cmd_name, "close") == 0){
	}
	else if(strcmp(cmd_name, "enter") == 0){
	}
	else if(strcmp(cmd_name, "leave") == 0){
	}
	else{
		fprintf(stderr, "Unknown command...\n");
	}
}

static void process_whisper(ClientData *client, char *msg){
	//Check whether msg size is correct
	if(strlen(msg) > CMD_MAX_SIZE){
		fprintf(stderr, "Message is to long.");
		return;
	}

	//Recover the receiver and the message to send
	msg++; //Skip first *
	char *receiver	= strtok(msg, "*");
	char *value		= strtok(NULL, "");

	//Receiver and value must be given
	if(receiver == NULL || value == NULL){
		fprintf(stderr, "Invalid command. Usage: *receiver* message\n");
		return;
	}
	value = str_trim(value);
	messaging_send_whisper(client->socket, client->login, receiver, value);
}


//------------------------------------------------------------------------------
// Public functions
//------------------------------------------------------------------------------

void prompt_cmd(ClientData *client){
	char str[CMD_MAX_SIZE];
	switch(client->status){
		case CONNECTED:
			fprintf(stdout, "%s > ", client->login);
			break;
		case CONNECTING:
			fprintf(stdout, "connecting > ");
			break;
		default:
			fprintf(stdout, "> ");
			break;
	}
	readline_stdin(str, CMD_MAX_SIZE);
	process_console_line(client, str);
}

void process_console_line(ClientData *client, char *str){
	//A command to execute in the server
	if(is_command(str) == TRUE){
		process_command(client, str);
		return;
	}
	//Whipser to specific user
	else if(is_whisper(str) == TRUE){
		process_whisper(client, str);
		return;
	}
	//Simple message to send to the server
}
