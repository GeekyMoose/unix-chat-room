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
//------------------------------------------------------------------------------
static void exec_connect(char *str){
	//If first elt is '\0', means no param given. Show usage
	if(*str == '\0'){
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

	//Check whether values are valid
	if(user_is_valid_name(username) == FALSE){
		fprintf(stderr, "Invalid username, size must be between %d and %d\n",
				USER_MIN_SIZE, USER_MAX_SIZE);
		return;
	}
	if(port == 0){
		port = PORT_DEFAULT;
	}

	//TODO Dev: to implements
	fprintf(stdout, "DEBUG: user: %s / server: %s / port: %d\n", username, servername, port);
	connect_to_server(servername, port);
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

static void process_command(char *cmd){
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
		exec_connect(args);
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

static void process_whisper(char *msg){
	//TODO
}


//------------------------------------------------------------------------------
// Public functions
//------------------------------------------------------------------------------

void prompt_cmd(){
	char str[CMD_MAX_SIZE];
	fprintf(stdout, "> ");
	readline_stdin(str, CMD_MAX_SIZE);
	process_console_line(str);
}

void process_console_line(char *str){
	//A command to execute in the server
	if(is_command(str) == TRUE){
		process_command(str);
		return;
	}
	//Whipser to specific user
	else if(is_whisper(str) == TRUE){
		process_whisper(str);
		return;
	}
	//Simple message to send to the server
	else{
		return;
	}
}
