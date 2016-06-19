/*
 * ----------------------------------------------------------------------------
 * C Library for the Unix Programming Project
 * Stream management
 *
 * June 19, 2016
 * Constantin MASSON
 * ----------------------------------------------------------------------------
 */
#include "stream.h"


// ----------------------------------------------------------------------------
// File management
// ----------------------------------------------------------------------------
/**
 * @brief			Read data from a stream
 * @details			buffsize should be inf or equals to actual buf size.
 *
 * @param fd		File descriptor to read
 * @param buf		Buffer to fill with read data
 * @param buffsize	Max nb of character to read
 * @return			Number of characters read (negative if error)
 */
int64_t bulk_read(int fd, char *buf, size_t buffsize){
	int		c;
	size_t	len=0;
	do {
		c = TEMP_FAILURE_RETRY(read(fd, buf, buffsize));
		if(c<0) {return c;}
		if(c==0) {return len;} //EOF
		buf			+=c; //Forward pointed address by c
		len			+=c;
		buffsize	-=c;
	} while(buffsize>0);
	return len;
}

/**
 * @brief			Write data in a file
 * @detail			Write maximum buffsize char (Must be inferior to actual buff size)
 *
 * @param fd		File descriptor where to write
 * @param buff		Buffer to fill
 * @param buffsize	Max number of char to write
 * @return			Number of written char (negative if error)
 */
int64_t bulk_write(int fd, char *buf, size_t buffsize){
	int		c;
	size_t	len=0;
	do{
		c = TEMP_FAILURE_RETRY(write(fd,buf,buffsize));
		if(c<0) {return c;}
		buf			+=c; //Forward pointed address by c
		len			+=c;
		buffsize	-=c;
	}while(buffsize>0);
	return len ;
}

/**
 * @brief			Add content in file
 * @details			Open the given file, add buf inside (To the end) and close file.
 * 					If buf size is more then 'len', only 'len' elements will be written
 *
 * @param filename	Path and name of the file to write
 * @param buf		Buffer with data to read
 * @param len		Max number of char to read from buff
 * @return			1 if successfully written, otherwise, return -1
 */
int append_to_file(char *filename, char *buf, size_t len){
	int fd, flags, perms;
	flags = O_WRONLY|O_APPEND|O_CREAT;
	perms = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;

	if((fd = TEMP_FAILURE_RETRY(open(filename, flags, perms)) )){
		perror("Open file");
		return -1;
	}
	if(bulk_write(fd, buf, len)<0){
		perror("Write");
		return -1;
	}
	if(TEMP_FAILURE_RETRY(close(fd))<0){
		perror("Close file");
		return -1;
	}
	return 1;
}

