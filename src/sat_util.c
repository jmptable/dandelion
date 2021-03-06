#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "list.h"
#include "sat.h"
#include "sat_util.h"

bool compatible_directions(Dir a, Dir b) {
	bool valid = true;

	if(a == UP && b == DOWN) {
	} else if(a == DOWN && b == UP) {
	} else if(a == LEFT && b == RIGHT) {
	} else if(a == RIGHT && b == LEFT) {
	} else {
		valid = false;
	}

	return valid;
}

bool connectable(Connector* a, Rot rotA, Connector* b, Rot rotB) {
	return compatible_directions((a->direction + rotA)%4, (b->direction + rotB)%4);
}

bool connection_is_valid(Connection* conn, Rot a, Rot b) {
	return compatible_directions((conn->child->direction + a)%4, (conn->parent->direction + b)%4);
}

int rot_x_pt(Pt* p, Rot r) {
	return rot_x(p->x, p->y, r);
}

int rot_y_pt(Pt* p, Rot r) {
	return rot_y(p->x, p->y, r);
}

int rot_x(int x, int y, Rot r) {
	switch(r) {
		case D0:
			return x;
			break;
		case D90:
			return -y;
			break;
		case D180:
			return -x;
			break;
		case D270:
			return y;
			break;
	}

	return 0;
}

int rot_y(int x, int y, Rot r) {
	switch(r) {
		case D0:
			return y;
			break;
		case D90:
			return x;
			break;
		case D180:
			return -y;
			break;
		case D270:
			return -x;
			break;
	}

	return 0;
}

Pt sprite_raster(unsigned int w, unsigned int h, unsigned int index) {
	int y = index/w;
	int x = index-y*w;
	return (Pt){ x, y };
}

// LIMIT: names must be less than 256 char long
SatPartInfo* info_by_name(char* name) {
	Node* last = sat_partinfos;

	while(last != NULL) {
		char* nname = ((SatPartInfo*)last->data)->name;
		if(strncmp(nname, name, 256) == 0)
			return (SatPartInfo*)last->data;
		last = last->next;
	}

	return NULL;
}

// LIMIT: names must be less than 256 char long
Satellite* sat_by_name(char* name) {
	Node* last = satellites;

	while(last != NULL) {
		char* nname = ((Satellite*)last->data)->name;
		if(strncmp(nname, name, 256) == 0)
			return (Satellite*)last->data;
		last = last->next;
	}

	return NULL;
}

Connector* connector_by_sig(SatPartInfo* info, int x, int y, Dir dir) {
	for(int i=0; i < info->num_connectors; i++) {
		Connector* c = info->connectors[i];
		if(c->position.x == x && c->position.y == y && c->direction == dir) return c;
	}

	return NULL;
}

// adds a part to the end of the linked list of all parts for the sat
/*
void append_part(struct Satellite* sat, struct SatPart* part) {
	struct SatPartNode* last = sat->first_part;
	
	// construct the new node
	struct SatPartNode* newNode = (struct SatPartNode*)malloc(sizeof(struct SatPartNode));
	newNode->part = part;
	newNode->next = NULL;

	if(last == NULL) {
		sat->first_part = newNode;
	} else {
		// find the last node
		while(last->next != NULL)
			last = last->next;
		last->next = newNode;
	}
}

struct SatPart* get_last_part(struct Satellite* sat) {
	struct SatPartNode* last = sat->first_part;

	// find the last node
	while(last->next != NULL)
		last = last->next;

	return last->part;
}*/
