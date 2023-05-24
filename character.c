#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "character.h"
#include "narrators.h"
#include "items.h"


enum directions
{
	DOWN,
	UP,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
};


struct character* createCharacter(char* name){
	
	struct character* player = (struct character*)malloc(sizeof(struct character));

	strcpy(player->name, name);
	player->inventory = NULL;
	player->location = NULL;	
	player->attr.health = 100;
	player->attr.cyberFatigue = 20;

	return  player;
}


void move(struct character* p, int direction){

	if(direction == DOWN && p->location->bellow != NULL){
	
		p->location = p->location->bellow;
	}
	else if(direction == UP && p->location->above != NULL){
	
		p->location = p->location->above;
	}
	else if(direction == LEFT && p->location->left != NULL){
	
		p->location = p->location->left;
	}
	else if(direction == RIGHT && p->location->right != NULL){
	
		p->location = p->location->right;
	}
	else if(direction == FORWARD && p->location->forward != NULL){
	
		p->location = p->location->forward;
	}
	else if(direction == BACKWARD && p->location->backward != NULL){
	
		p->location = p->location->backward;
	}
	else{
		printf("\nThere is nothing that way.\n");
		return;
	}
	char path[100] = "./story/Cells/";
	strcat(path, p->location->cellname);
	system("clear");
	narrateFile(path, 5000);
}


void search(struct character* p){

	if(p->location->cellItem != NULL){
	
		if(p->inventory == NULL){
		
			p->inventory = p->location->cellItem;
			narrate("You found: ", 10000);
			printf("%s!", p->location->cellItem->itemName);
			p->location->cellItem = NULL;
			enterQToContinue();
		}
		else{
		
			p->location->cellItem->nextItem = p->inventory;
			p->inventory = p->location->cellItem;
			narrate("You found: ", 10000);
			printf("%s!", p->location->cellItem->itemName);
			p->location->cellItem = NULL;
			enterQToContinue();
		}	
	}
	else{
		
		narrate("\nYou found nothing useful.", 10000);
		enterQToContinue();
	}

}


void searchTerminal(int cellid){

	if(cellid == 16){
	
	char terminalPassword[30];
	char terminalContinue[30];

	while(1){
		printf("/>> Enter password: ");
		scanf("%s", terminalPassword); 
		if(strcmp(terminalPassword, "c0ckp1td00r") == 0){
		
			narrate("\n\tYour fingertips dance on the keyboard, the screen unlocks and a familiar rush of euphoria fills your body,\n"\
			"the deceased owner of this terminal possessed hundreds of terrabytes of clasified data about every corp in the solar system.\n"\
			"After hours of reading through the data you find an archive about a depopulation plan, turns out the bacterial infection that\n"\
			"killed everyone on the station wasn't an accident at all, you were the lab rats of a new strain of bacteria that was  being tested\n"\
			"as a depopulation agent. If Earthers find out you possess this data they will nuke the whole station, you gotta upload this data to a safe\n"\
			"location immediatly. You gotta find a way to jack in Martian cyberspace and transfer this to a secure repository on Mars.", 10000);
			enterQToContinue();
			return;
		}
		else{	system("clear");
			puts("wrong password");
			printf("\nDo you want to continue [yes/no] />> ");
			scanf("%s", terminalContinue);
			if(strcmp(terminalContinue, "no") == 0){
				return;
			}
		    }
		}
	}

	switch(cellid){
	
	
		case 0:
			narrate("\nThis is your terminal, you already know everything about it.",10000);
			enterQToContinue();
			break;
			
		case 7:
			narrate("\nThis guy was into some weird shit, and he didnt even bother deleting his browsing history.\nNothing usefull to be found here.",10000);
			enterQToContinue();
			break;
		case 21:
			narrate("\n\t\tThis terminal definiterly belonged to a fellow hacker, its full of leaked data and hacking software,\n"\
					"it's really weird that this guy left his terminal unlocked, like he wanted someone to access it,\n"\
				       	"it seems that he was trying to gain access to the terminal at cell 16.\n"\
					"Searching for saved passwords you find the following password ---> c0ckp1td00r.",10000);
			enterQToContinue();
			break;
		case 24:
			narrate("\nPeople really are searching the most fucked up shit on the internet, nothing to be found here.",10000);
			enterQToContinue();
			break;
		default:	
			narrate("\nThere are no terminals in this cell.",10000);
			enterQToContinue();
			break;
	}


}


void listInventory(struct character* p, int type){

	if(p->inventory == NULL && type == 0){
	
		printf("\nInventory is empy.\n");
		return;
	}
	else{
		printf("\n\n\n******INVENTORY******\n");	
		struct item* temp = p->inventory;
		if(temp == NULL){
			printf("\n\n---EMPTY---\n\n\n");
		}
		while(temp != NULL){
		
			printf("[ %s ] ID: %s\n",temp->itemName, temp->activator);
			temp = temp->nextItem;
		}
		printf("*********************");	
	}
}



int isInInventory(struct character* p, int id){

	struct item* temp = p->inventory;
	
	while(temp != NULL){
	
		if(temp->itemId == id){return true;}
		temp = temp->nextItem;
	}
	return false;
}



void removeFromInventory(struct character* p, int itemid){

	
	if(p->inventory->itemId == itemid){
		p->inventory = p->inventory->nextItem;
		return;
	}
	else{
	
	struct item* temp = p->inventory->nextItem;
	struct item* previous = p->inventory;
	
	while(temp != NULL){
	
		if(temp->itemId == itemid){
			previous->nextItem = temp->nextItem;
			return;
		}
		previous = temp;
		temp = temp->nextItem;
	}
	}
}


int chooseItem(struct character* p){

	if(p->inventory != NULL){
	
		narrate("\nChoose item[ID] >> ", 10000);
		return 0;	
	}
	else{
		narrate("\nEnter anything to continue >> ", 10000);
		return -1;
	}
}


int useItem(struct character* p, char* item, int f){

	struct item* temp = p->inventory;

	while(temp != NULL){
			
		if(strcmp(item, temp->activator) == 0){return temp->itemId;}
		temp = temp->nextItem;
	}
	if(f == 0){
		printf("\nItem not found.");
		enterQToContinue();
	}
	return -1;
}


void showStats(struct character* p){

	system("clear");
	
	printf("Name: %s\n", p->name);
	printf("Location: %s\n", p->location->cellname);
	printf("Health: %d\n", p->attr.health);
	printf("Cyberfatigue: %d", p->attr.cyberFatigue);

	listInventory(p, 1);
	
}


void showDirections(struct character* p){
	system("clear");
	if(p->location->above != NULL){printf("\n\nUP -> %s\n", p->location->above->cellname);}
	if(p->location->bellow != NULL){printf("DOWN ->%s\n", p->location->bellow->cellname);}
	if(p->location->left != NULL){printf("LEFT ->%s\n", p->location->left->cellname);}
	if(p->location->right != NULL){printf("RIGHT ->%s\n", p->location->right->cellname);}
	if(p->location->forward != NULL){printf("FORWARD ->%s\n", p->location->forward->cellname);}
	if(p->location->backward != NULL){printf("BACK ->%s\n", p->location->backward->cellname);}
}


void jackIn(struct character* p, int indicator){
	
	

	if(p->attr.cyberFatigue < 100){

		switch(indicator){
	
			case 0:
				narrate("\nYour spine is filled with the familiar sensation as your mind drops into cyberspace,\n"\
				"none of your contacts are online, you spend some time checking the usual chatrooms but there is nothing going on right now,\n"\
			       	"after a while you get bored, you unplug and return to meatspace.", 10000);
				setAttr(p, GAIN_CYBERFATIGUE, 20);
				enterQToContinue();
				break;

			case 7: 
				narrate("\nThis has to be one of the most uncomfortable Cyberdives you've ever done, the cyberlink on this terminal is unmaintained and glitchy, "\
				"there's also nothing of importance on the computer either, and there is no network card "\
				"so you cannot access outter cyberspace from this machine.\n", 10000);
				setAttr(p, GAIN_CYBERFATIGUE, 40);
				enterQToContinue();
				break;

			case 16:
		       		narrate("\nThere is no cyberlink interface on this terminal, you should use the monitor and keyboard to access it.\n", 10000);
				enterQToContinue();
				break;

			case 21:
		       		narrate("\nThe cyberlink interface on this machine is top notch, your mind slides into cyberspace like warm honey, \n"\
				"the bad news is, the previous owner has remote cyberspace services locked with strong encryption so only the local \n"
				"machine is accessible, you look around and find a lot of reconnaissance information about the terminal on cell 16,\n"\
				"You also find a text file containing the password ---> c0ckp1td00r", 10000);
				setAttr(p, GAIN_CYBERFATIGUE, 10);
				enterQToContinue();
				break;

			case 24:
		       		narrate("\nAs your perception gets sucked into the machines guts you feel like your soul is rubbing on sandpaper.\n"\
				"This is definitely the nastiest cyberdive you've ever attempted,\nand its all for nothing since this machine has neither a network card"\
				"nor a functional cyberlink card, there is nothing that you can do from here,\nyou pull the plug from your head and open your eyes,\n"\
				"this is the first time that you are actually happy to be back in meatspace.", 10000);
				setAttr(p, GAIN_CYBERFATIGUE, 60);
				setAttr(p, LOSE_HEALTH, 30);
				enterQToContinue();
				break;

		}
	
		if(p->attr.cyberFatigue > 100){
			
			p->attr.cyberFatigue = 100;
			setAttr(p, LOSE_HEALTH, 50);
			narrate("\nThat last dive left you feeling like electricity is running through your spine, you need to relax your "\
			"nervous system before jacking in again", 10000);
			enterQToContinue();
		}
	}
	else{
	
		narrate("\nYour nervous system is fried, you need to find a way to calm down before you can jack in again, maybe eat or drink something.", 10000);
		enterQToContinue();
	}
}



void terminalDialog(int indicator){
	
	switch(indicator){

		case 0:
			narrate("\nYou look at your terminal's Cyberlink slot, are you sure you wanna jack in?[yes/*] >> ", 10000);
			break;
		case 7: 
			narrate("\nThe terminal infont of you is in bad condition, the previous owner probably didn't care much about it, "\
			"are you sure you wanna link here?[yes/*]  >> ", 10000);
			break;

		case 16:
		       	narrate("\nThe terminal in this cell looks nice and clean, theres also severa DIY augmentations installed,"\
			"but you dont see a cyberlink port are you sure you wanna link?[yes/*] >> ", 10000);
			break;

		case 21:
		       	narrate("\nThis terminal is full of cybersec software you are familiar with, are you sure you wanna cyber dive here?[yes/*] >> ", 10000);
			break;

		case 24:
		       	narrate("\nThe terminal infront of you looks vile, you've never seen a terminal in such a bad condition, are you sure?[yes/*] >> ", 10000);
			break;
		default:
			narrate("\nThere are no terminals in this cell.[*/*] >> ", 10000); 
			break;

	}
}



int isThereATerminal(struct character* p){

	if(p->location->cellID == 0 || p->location->cellID == 7 || p->location->cellID == 16
	|| p->location->cellID == 21 || p->location->cellID == 24){
	
		return p->location->cellID;
	
	}
	else{
		return -1;
	}
}


void setAttr(struct character* p, int attr, int points){

	switch(attr)
	{
		case 0:
			p->attr.health += points;
			break;
		case 1:
			p->attr.health -= points;
			break;
		case 2:
			p->attr.cyberFatigue += points;
			break;
		case 3:
			p->attr.cyberFatigue -= points;
			break;
	}	
	if(p->attr.cyberFatigue < 0){
	
		p->attr.cyberFatigue = 0;
	}
	else if(p->attr.cyberFatigue > 100){
	
		p->attr.cyberFatigue = 100;
	}
	if(p->attr.health < 0){
	
		p->attr.cyberFatigue = 0;
	}
	else if(p->attr.health > 100){
	
		p->attr.health = 100;
	}
}
