#include <stddef.h>
#include <stdbool.h>
#include <string.h>


#include "narrators.h"
#include "character.h"

enum items{

	solderingiron,
	oldcyberdeck,
	longrangeantenna,
	moonshinefromthemoon,
	proteinbar,
	waterbottle,
	wirestripper,
	screwdriver,
	sedatives,
	cbdoil,
	cannabisjoint,
	lighter
	  };

struct item solderingIron = {0, "si", "Soldering iron", NULL};
struct item oldCyberDeck = {1, "ocd", "Unresponsive Old Cyberdeck", NULL};
struct item antenna = {2, "lra", "Long Range Antenna", NULL};
struct item moonshine = {3, "mftm", "Moonshine from the moon", NULL};
struct item proteinBar = {4, "npb", "Nutritious Protein Bar", NULL};
struct item waterBottle = {5, "wb", "Water Bottle", NULL};
struct item wireStripper = {6, "ws", "Wire Stripper", NULL};
struct item screwDriver = {7, "sc", "Screwdriver", NULL};
struct item Sedatives = {8, "se", "Sedatives", NULL};
struct item cbdOil = {9, "cbd", "CBD Oil", NULL};
struct item cannabisJoint = {10, "cj", "Cannabis Joint", NULL};
struct item Lighter = {11, "li", "Lighter", NULL};


struct item** initItemArray(void){

	struct item** itemsArray = (struct item**)malloc(sizeof(struct item*) * 26);
	
	for(int i = 0; i <= 26; i++){
		
		itemsArray[i] = (struct item*)malloc(sizeof(struct item));
	}	
	
	for(int i = 0; i <= 26; i++){
	
		itemsArray[i] = NULL;
	}

	itemsArray[6] = &solderingIron;
	itemsArray[7] = &oldCyberDeck;
	itemsArray[19] = &antenna;
	itemsArray[14] = &moonshine;
	itemsArray[23] = &proteinBar;
	itemsArray[22] = &waterBottle;
	itemsArray[26] = &wireStripper;
	itemsArray[16] = &screwDriver;
	itemsArray[3] = &Sedatives;
	itemsArray[8] = &cbdOil;
	itemsArray[9] = &cannabisJoint;
	itemsArray[11] = &Lighter;
	return itemsArray;
}


void itemFunctions(struct character* p, int id){
	
	void (*funcArray[15])(struct character* p);
	funcArray[0] = si;
	funcArray[1] = ocd;
	funcArray[2] = lra;
	funcArray[3] = mftm;
	funcArray[4] = npb;
	funcArray[5] = wb;
	funcArray[6] = ws;
	funcArray[7] = sc;
	funcArray[8] = se;
	funcArray[9] = cbd;
	funcArray[10] = cj;
	funcArray[11] = li;

	funcArray[id](p);
}


void si(struct character* p){
	
	if(isInInventory(p, oldcyberdeck) && isInInventory(p, wirestripper)){
	if(strcmp(oldCyberDeck.itemName, "Old Cyberdeck") == 0 || strcmp(oldCyberDeck.itemName, "Old Cyberdeck with antenna") == 0){
		
		narrate("You already fixed the Cyberdeck, there's nothing else to solder.", 10000);
		enterQToContinue();

	}
	else{	
	narrate("\n\n\nAfter soldering a few wires back in place the Cyberdeck screen lights up to reveal the boot sequence.", 10000);
	strcpy(oldCyberDeck.itemName, "Old Cyberdeck");
	enterQToContinue();
	}
	}
	else if(isInInventory(p, oldcyberdeck)){
	narrate("\n\n\nYou could solder the loose wires in the Cyberdeck, but you need something to strip them off with so you can solder "\
	"them back in place.", 10000);
	enterQToContinue();
	}
}


void ocd(struct character* p){
	
	if(strcmp(oldCyberDeck.itemName, "Old Cyberdeck with antenna") == 0){
	
		narrate("\nThe antenna is installed, accessing the martian Cyberspace is most "\
		"Earth's netrunners dream,\n the realization that you will finally experience it "\
		"fills your gut with adrenaline,\n all you have to do now is link with the Cyberdeck.", 10000);
		enterQToContinue();
	}
	else if(strcmp(oldCyberDeck.itemName, "Old Cyberdeck") == 0){
	
		narrate("\nThis Old Cyberdeck contains the cryptographic keys to access Mar's "\
		"main access point,\nif you jack in from this Cyberdeck you can access the "\
		"martian Cyberspace. \nThe bad news are, there is no antenna on the\n "\
		"Cyberdeck, you need to find an antenna and install it.", 10000);
		enterQToContinue();
	}
	else{
		narrate("\nThe Cyberdeck is not powering up, after closer inspection you see that\n some wires are cut, you need to solder them back to make it work.", 10000);
		enterQToContinue();
	}
}
void lra(struct character* p){

	if(strcmp(oldCyberDeck.itemName, "Old Cyberdeck") == 0 && isInInventory(p,screwdriver))
	{
		narrate("\nYou install the antenna tightly on the Cyberdeck, "\
		"now it should be functional.", 10000);
		strcpy(oldCyberDeck.itemName, "Old Cyberdeck with antenna");
		removeFromInventory(p, longrangeantenna);
		enterQToContinue();
	}
	else if(strcmp(oldCyberDeck.itemName, "Old Cyberdeck") == 0){
	
		narrate("\nYou need a screwdriver to install the antenna on the Cyberdeck.\n"\
		"There should be one lying around somewhere.", 10000);
		enterQToContinue();
	}
	else{
		narrate("\nGeneral use long range antenna, it can be installed on many different "\
		"types of hardware if you have the know how.", 10000);
		enterQToContinue();
	}	
}
void mftm(struct character* p){

	narrate("\nDrinking the moonshine makes your stomach revolt,\nbut it gives "\
	"your nervous system the relaxation it desperately needed.", 10000);
	setAttr(p, LOSE_HEALTH, 20);
	setAttr(p, LOSE_CYBERFATIGUE, 50);
	if(p->attr.cyberFatigue < 0){p->attr.cyberFatigue = 0;}
	removeFromInventory(p, moonshinefromthemoon);
	enterQToContinue();
}
void npb(struct character* p){
	narrate("\nYou eat the delicious snack and immediately feel better.", 10000);
	setAttr(p, GAIN_HEALTH, 20);
	setAttr(p, LOSE_CYBERFATIGUE, 20);
	removeFromInventory(p, proteinbar);
	enterQToContinue();
}
void wb(struct character* p){

	narrate("\nYou chug the bottle, you were severely dehydrated.", 10000);
	setAttr(p, GAIN_HEALTH, 20);
	setAttr(p, LOSE_CYBERFATIGUE, 20);
	removeFromInventory(p, waterbottle);
	enterQToContinue();
}
void ws(struct character* p){

	narrate("\nA pair of wirestrippers, nothing more nothing less.", 10000);
	enterQToContinue();
}
void sc(struct character* p){

	narrate("\nGood ol screwdriver, the only constant in an evershifting world.", 10000);
	enterQToContinue();
}
void se(struct character* p){

	narrate("\nYou pop the one and only pill in the box, immediately feeling better.", 10000);
	setAttr(p, LOSE_CYBERFATIGUE, 40);
	removeFromInventory(p, sedatives);
	enterQToContinue();
}
void cbd(struct character* p){

	narrate("\nYou consume the cbd oil capsule, after a while you start relaxing.", 10000);
	setAttr(p, LOSE_CYBERFATIGUE, 20);
	removeFromInventory(p, cbdoil);
	enterQToContinue();
}
void cj(struct character* p){

	if(isInInventory(p, lighter)){
	
		narrate("\nYou light up and relax, your nerves needed that.", 10000);
		setAttr(p, LOSE_CYBERFATIGUE, 20);
		removeFromInventory(p, cannabisjoint);
		enterQToContinue();
	}
	else{	
	
		narrate("You need a lighter.", 10000);
		enterQToContinue();
	}
}
void li(struct character* p){

	narrate("\nA common lighter, it can come handy in many different situations.", 10000);
	enterQToContinue();
}
