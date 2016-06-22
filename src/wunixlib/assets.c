/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Assets functions and maccros
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */

#include "assets.h"

int readline_stdin(char buff[], int size){
	char c;
	int pos = 0;
	while(--size > 0 && ( (c=getchar()) != EOF && c != '\n')){
		buff[pos++] = c;
	}
	buff[pos] = '\0';
	if(c != '\n'){
		//If user stack overflow, clear buffer
		clear_buffer();
	}
	return pos;
}

void clear_buffer(){
	char c;
	while( (c=getchar()) != EOF && c != '\n');
}
