#ifndef ITEMS_H
#define ITEMS_H

#include <stdlib.h>
struct character;
struct item {

	int itemId;
	char activator[10];
	char itemName[30];
	struct item* nextItem;

};

struct item** initItemArray(void);
void itemFunctions(struct character* p, int id);

void si(struct character* p);
void ocd(struct character* p);
void lra(struct character* p);
void mftm(struct character* p);
void npb(struct character* p);
void wb(struct character* p);
void ws(struct character* p);
void sc(struct character* p);
void se(struct character* p);
void cbd(struct character* p);
void cj(struct character* p);
void li(struct character* p);



#endif
