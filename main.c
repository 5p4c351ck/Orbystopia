#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"
#include "narrators.h"
#include "choice.h"


int main(void){

	extern struct item oldCyberDeck;
	system("clear");
	
	narrateFile("./story/Orbystopia", 10000);
	
	narrate("\n\n\nEnter your name: ", 5000);
	char name[30];
	scanf("%s", name);
	system("clear");
	struct item** itemsArray = initItemArray();
	struct cell**  map = initGrid(itemsArray);
	struct character* player = createCharacter(name);
	player->location = map[0];
	
	narrateFile("./story/prologue", 10000);
	enterQToContinue();
	narrateFile("./story/start", 10000);
	enterQToContinue();
		

	while(1){
		
		system("clear");
		printf("CELL: %d HP: %d >> ", player->location->cellID, player->attr.health);	
		for(int i = 0; i < 2; i++){
			
			char fchoice[100];
			char schoice[100];	
			
			if(i == 0){
				
			scanf("%s", fchoice);		
			}
			else if(i == 1){
			scanf("%s", schoice);
			}
			
			if(strcmp(fchoice, "float") == 0){
				if(i == 0){
					narrate("With a spastic move you propel yourself [direction] >>  ", 10000);
					continue;
				}
				move(player,choseDirection(schoice));
				enterQToContinue();
			}
			else if(strcmp(fchoice, "show") == 0){
				if(i == 0){
					narrate("[stats/directions] >>  ", 10000);
					continue;
				}
			
				if(strcmp(schoice, "stats") == 0){
				
					showStats(player);
					enterQToContinue();
				}
				else if(strcmp(schoice, "directions") == 0){
				
					showDirections(player);
					enterQToContinue();
				}
			}
			else if(strcmp(fchoice, "search") == 0){
			
				if(i ==0){
					narrate("What do you want to search? [cell/terminal] >>  ", 10000);
					continue;
				}
				if(strcmp(schoice, "cell") == 0){
					
					search(player);
				}
				else if(strcmp(schoice, "terminal") == 0){

					searchTerminal(player->location->cellID);
				}	
				else{
				
					narrate("\nInvalid option.", 10000);
					enterQToContinue();
				}
			}	
			else if(strcmp(fchoice, "use") == 0){
				int f;
				int item_id;	
				if(i == 0){
					listInventory(player, 0);
					f = chooseItem(player);
					continue;
				}
				item_id = useItem(player, schoice, f);
				if(item_id != -1){
				itemFunctions(player, item_id);
				}
			}
			else if(strcmp(fchoice, "link") == 0){
				int terminalExists;
				if(i == 0){
					if(strcmp(oldCyberDeck.itemName, "Old Cyberdeck with antenna") == 0){
						narrateFile("./story/end", 10000);
						enterQToContinue();
						exit(EXIT_SUCCESS);
					}
					terminalExists = isThereATerminal(player);
					terminalDialog(terminalExists);
					continue;
				}
				if((strcmp(schoice, "yes") == 0) && (terminalExists != -1)){
				
					jackIn(player, isThereATerminal(player));
				}
			}
			else if(strcmp(fchoice, "quit") == 0){
				
				exit(EXIT_SUCCESS);
			}
			else if(strcmp(fchoice, "help") == 0){
				system("clear");	
				narrateFile("./story/help", 10000);
				continue;
				printf("enter anything to continue [*]>> ");
			}
		}
	
		if(player->attr.health <= 0){
			
			gameOver();	
		}
	}

	
	return 0;
}
