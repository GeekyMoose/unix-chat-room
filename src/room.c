// -----------------------------------------------------------------------------
/**
 * \file	room.c
 * \author	Constantin MASSON
 * \date	June 23, 2016
 *
 * \brief	Room component
 * \note	C Library for the Unix Programming Project
 */
// -----------------------------------------------------------------------------

#include "room.h"


// -----------------------------------------------------------------------------
// General Functions
// -----------------------------------------------------------------------------

Room* room_create(User *owner, const char *name){
	assert(owner != NULL);
	Room *room;
	room = (Room*)malloc(sizeof(Room));
	if(room == NULL){
		return NULL;
	}
	memset(room, 0x00, sizeof(Room));
	list_init(&(room->list_users), NULL);
	strcpy(room->owner_name, owner->login);
	strcpy(room->name, name);
	return room;
}

int room_destroy(Room *room){
	assert(room != NULL);
	free(room);
	return 1;
}

int room_is_valid_name(const char *name){
	if(name == NULL){ return -1; }
	size_t size = strlen(name);
	return (size < ROOM_MIN_SIZE || size > ROOM_MAX_SIZE) ? -1 : 1;
}


// -----------------------------------------------------------------------------
// List function implementations
// -----------------------------------------------------------------------------

int room_match_name(void* room, void* name){
	Room r = *(Room*) room;
	name = (char*) name;
	if(strcmp(r.name, name) == 0){
		return 1;
	}
	return 0;
}

int room_display(void* room){
	if(room == NULL){
		fprintf(stdout, "Room is null\n");
		return 1;
	}
	Room r = *(Room*) room;
	fprintf(stdout, "Room name: '%s'\n", r.name);
	return 1;
}
