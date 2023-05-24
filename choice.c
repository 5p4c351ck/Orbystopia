#include <string.h>


#include "choice.h"


int choseDirection(char* direction){
	
	if(strcmp(direction, "down") == 0){
		return 0;
	}
	else if(strcmp(direction, "up") == 0){
		return 1;
	}
	else if(strcmp(direction, "left") == 0){
		return 2;
	}
	else if(strcmp(direction, "right") == 0){
		return 3;
	}
	else if(strcmp(direction, "forward") == 0){
		return 4;
	}
	else if(strcmp(direction, "back") == 0){
		return 5;
	}
	else{
		return -1;
	}
}
