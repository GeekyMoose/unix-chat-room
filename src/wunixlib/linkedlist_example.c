
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"


typedef struct _a{
	char*name;
	int id;
}user;

int display_player(void *data){
	user u = *(struct _a*)data;
	fprintf(stdout, "User name: %s / ID: %d\n", u.name, u.id);
	return 1;
}

void test_struct_list(){
	Linkedlist list;
	list_init(&list, NULL);

	user u1 = {"User 1", 1};
	user u2 = {"User 2", 2};
	list_append(&list, &u1);
	list_append(&list, &u2);

	list_iterate(&list, display_player);
	list_clear(&list);
}

int main(int argc, char **argv){
	fprintf(stdout, "Linkedlist - Use case Example\n");
	test_struct_list();
	fprintf(stdout, "Linkedlist - Example done\n");
	return EXIT_SUCCESS;
}

