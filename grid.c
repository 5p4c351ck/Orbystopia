#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grid.h"
#include "items.h"

struct cell** initGrid(struct item** itemsArray){
	
	struct cell** orbyagrid = (struct cell**)malloc(sizeof(struct cell*) * 26);


	for(int i = 0; i <= 26; i++){
		orbyagrid[i] = (struct cell*)malloc(sizeof(struct cell));
	}

	for (int i = 0; i <= 26; i++){
		
		char buffer[10];
		orbyagrid[i]->cellID = i;
		sprintf(buffer, "Cell %d", i);
		strcpy(orbyagrid[i]->cellname, buffer);
		orbyagrid[i]->cellItem = itemsArray[i];
		if(orbyagrid[i]->cellID % 3 == 0){				/* check if the cell is at the rightmost leftmost or middle
							  	        side of the grid and set its neighboors accordingly */   
			orbyagrid[i]->right = NULL;		
			orbyagrid[i]->left = orbyagrid[i + 1];
		}
		else if(orbyagrid[i]->cellID % 3 == 2){		
								 
			orbyagrid[i]->right = orbyagrid[i -1];	
			orbyagrid[i]->left = NULL;
		}
		else{
			orbyagrid[i]->right = orbyagrid[i -1];	
			orbyagrid[i]->left = orbyagrid[i + 1];
		}
		
		
									/* check if we are at the top middle or lowest side */
		if(orbyagrid[i]->cellID == 0){
			
			orbyagrid[i]->above = orbyagrid[i + 9];
			orbyagrid[i]->bellow = NULL;
		}
		else if(floor((double)(orbyagrid[i]->cellID / 9)) == 0){
		
			orbyagrid[i]->above = orbyagrid[i + 9];	
			orbyagrid[i]->bellow = NULL;
		}
		else if(floor((double)(orbyagrid[i]->cellID / 9)) == 1){
			
			orbyagrid[i]->above = orbyagrid[i + 9];	
			orbyagrid[i]->bellow = orbyagrid[i - 9];
		}
		else if(floor((double)(orbyagrid[i]->cellID / 9)) == 2){
			
			orbyagrid[i]->above = NULL;	
			orbyagrid[i]->bellow = orbyagrid[i - 9];
		}
									/* check if we are at the front middle or back side */
	

		if(orbyagrid[i]->cellID % 9 <= 2){
		
			orbyagrid[i]->forward = orbyagrid[i + 3];	
			orbyagrid[i]->backward = NULL;
		}
		else if((orbyagrid[i]->cellID % 9 >= 3) && (orbyagrid[i]->cellID % 9 <= 5)){
		
			orbyagrid[i]->forward = orbyagrid[i + 3];	
			orbyagrid[i]->backward = orbyagrid[i - 3];
		}
		else if(orbyagrid[i]->cellID % 9 >= 6){
		
			orbyagrid[i]->forward = NULL;	
			orbyagrid[i]->backward = orbyagrid[i - 3];
		}
	}	
	return orbyagrid;

}
