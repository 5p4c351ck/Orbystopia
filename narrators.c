#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#include "narrators.h"


void narrate(const char* text, int delay){
	
	while(*text != '\0'){
		putchar(*text);
		fflush(stdout);
		text++;
		usleep(delay);
	}

}

void narrateFile(const char* filename, int delay){
	
	char buffer[10];
	FILE* file = fopen(filename, "r");
	if(file == NULL){
		return;
	}
	while(fscanf(file, "%c", buffer) != EOF){
	
		narrate(buffer, delay);
	}
	fclose(file);
}

void enterQToContinue(void){
	puts("\n\n\nEnter 'q' to continue");
	char c;
	while(c != 'q'){
		c = getchar();
	}
	system("clear");
	return;
}


void gameOver(void){

	narrate("Everything turns dark, as you collapse on the ethereal  bed created by gravitys absence.", 10000);
	narrate("\n\n\n				GAME OVER			\n\n\n", 10000);
	enterQToContinue();		
	exit(EXIT_SUCCESS);
}
