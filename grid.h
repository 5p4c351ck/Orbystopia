#ifndef GRID_H
#define GRID_H


struct cell {

	int cellID;
	char cellname[20];
	struct item* cellItem;
	struct cell* above;
	struct cell* bellow;
	struct cell* left;
	struct cell* right;
	struct cell* forward;
	struct cell* backward;
};

struct cell** initGrid(struct item** itemsArray);

#endif
