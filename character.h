#ifndef CHARACTER_H
#define CHARACTER_H

#include "items.h"
#include "grid.h"

#define GAIN_HEALTH 0
#define LOSE_HEALTH 1
#define GAIN_CYBERFATIGUE 2 
#define LOSE_CYBERFATIGUE 3


enum directions;

struct character {

	char name[20];
	struct item* inventory;
	struct cell* location;

	struct attributes {
		int health;
		int cyberFatigue;
		}attr;
	};


struct character* createCharacter(char* name);
void move(struct character* p, int direction);
void search(struct character* p);
void searchTerminal(int cellid);
void listInventory(struct character* p, int type);
int isInInventory(struct character* p, int itemid);
void removeFromInventory(struct character* p, int itemid);
int chooseItem(struct character* p);
int useItem(struct character* p, char* item, int f);
void showStats(struct character* p);
void showDirections(struct character* p);
void jackIn(struct character* p, int);
void terminalDialog(int indicator);
int isThereATerminal(struct character* p);
void setAttr(struct character* p, int attr, int points);

#endif
