#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int main() {
	printf("What is it like to be Goldie?\n\n\n");
	bool dirty = false; // using macro from stdbool.h
	bool locsDirty[4] = {false, false, false, false};
	bool bowlFull = false;
	unsigned int energy = 7; // will range from 0-7
	unsigned int posture = 1; // will range from 0-2 lying down, sitting, standing... sleeping is a separate verb available when lying down on the armchair
	#define LYING 0
	#define SITTING 1
	#define STANDING 2
	unsigned int loc = 0; // will range from 0-3;
	#define ARMCHAIR 0
	#define HALL_DOOR 1
	#define FOOD_BOWL 2
	#define BACK_DOOR 3
	#define ARMCHAIR_COM
//	#define HALL_DOOR_COM 
//	#define FOOD_BOWL_COM 
//	#define BACK_DOOR_COM
	char locVerbs[4][21]  = {"go to your armchair", "go to the hall door", "go to your food bowl", "go to the back door"};
	char postureVerbs[3][12]  = {"lie down", "sit upright", "stand"};
	char options[5][21]; // will hold available verbs as strings used both for prompting the player and in a switch statement
	int optionsCount;
	char input[100]; // to avoid errors in case user input multiple characters before pressing return key
	srand((unsigned) time(NULL)); // cast to avoid compiler warning
	for(;;) {
		optionsCount = 0; // start with no options available, we'll add them in now
		// determine options and fill options array while totting up how many options we have
		if (dirty) {
			strcpy(options[optionsCount++], "clean your paws");
		}
		strcpy(options[optionsCount++], "miaow");
		if (loc == ARMCHAIR) {
			//if (posture == LYING) {
			strcpy(options[optionsCount++], "sleep");
			//}
			strcpy(options[optionsCount++], locVerbs[loc + 1]);
		}
		else if (loc == FOOD_BOWL) {
			if (bowlFull) {
				strcpy(options[optionsCount++], "eat");
			}
			strcpy(options[optionsCount++], locVerbs[loc + 1]);
			strcpy(options[optionsCount++], locVerbs[loc - 1]);
		}
		else if (loc == HALL_DOOR) {
			strcpy(options[optionsCount++], locVerbs[loc + 1]);
			strcpy(options[optionsCount++], locVerbs[loc - 1]);			
		}
		else if (loc == BACK_DOOR) {
			strcpy(options[optionsCount++], "sleep");
			strcpy(options[optionsCount++], locVerbs[loc - 1]);			
		}
		/*
		if (posture == LYING || posture == SITTING) {
			strcpy(options[optionsCount++],  postureVerbs[posture + 1]);
		}
		if (posture == SITTING || posture == STANDING) {
			strcpy(options[optionsCount++], postureVerbs[posture - 1]);
		}
		*/

		// display game world status
		if (loc == HALL_DOOR) {
			printf("You are in the living room, near the hall door. ");
			if (locsDirty[HALL_DOOR]) {
				printf("There are muddy pawprints here. ");
			}
		}
		else if (loc == ARMCHAIR) {
			printf("You are in the living room, perched on your armchair. ");
			if (locsDirty[ARMCHAIR]) {
				printf("Someone has left streaks of mud on it.");
			}
		}
		else if (loc == FOOD_BOWL) {
			printf("You are in the kitchen, near to your food bowl. ");

			if (bowlFull) {
				printf("It is heaped with food. ");
			}
			else {
				printf("It is just about empty. ");
			}
			if (locsDirty[FOOD_BOWL]) {
				printf("There are muddy tracks on the floor. ");
			}
		}
		else if (loc == BACK_DOOR) {
			printf("You are in the kitchen, on the doormat by the back door. ");
		}
		if (dirty) {
			printf("Your paws are muddy. ");
		}
		if (energy < 3) {
			printf("You feel rather like having a rest. ");
		}
		locsDirty[loc] = dirty;
		printf("\n");
		printf("Some of your humans are nearby.\n");
		printf("Press ");
		for (int i = 0; i < optionsCount - 1; i++) {
			char str[50] = "%u to ";
			char verb[21];
			strcpy(verb, options[i]);
			strcat(str, verb);
			strcat(str, ", ");
			printf(str, i);
		}
		char str[50] = "%u to ";
		char verb[21];
		strcpy(verb, options[optionsCount - 1]);
		strcat(str, verb);
		strcat(str, ", or any other key to quit.\n");
		printf(str, optionsCount - 1);
		unsigned char c;
		scanf(" %c", &c);
		//printf("Command received.");
		unsigned int command = c - 48;
		char comStr[21];
		strcpy(comStr, options[command]);
		bool alerting = false;
		if (strcmp(comStr, "go to your armchair") == 0) {
			loc = ARMCHAIR;
			printf("You ");
			printf(locVerbs[loc]);
			printf(".");
		}
		else if (strcmp(comStr, "go to the hall door") == 0) {
			loc = HALL_DOOR;
			printf("You ");
			printf(locVerbs[loc]);
			printf(".");
		}
		else if (strcmp(comStr, "go to your food bowl") == 0) {
			loc = FOOD_BOWL;
			printf("You ");
			printf(locVerbs[loc]);
			printf(".");
		}
		else if (strcmp(comStr, "go to the back door") == 0) {
			loc = BACK_DOOR;
			printf("You ");
			printf(locVerbs[loc]);
			printf(".");
		}
		else if (strcmp(comStr, "clean your paws") == 0) {
			if (dirty) {
				dirty = false;
			}
			printf("You clean your paws.");
		}
		else if (strcmp(comStr, "eat") == 0) {
			bowlFull = false;
			printf("You eat a bowl of dried food.");
		}
		else if (strcmp(comStr, "sit") == 0) {
			posture = SITTING;
		}
		else if (strcmp(comStr, "lie down") == 0) {
			posture = LYING;
		}
		else if (strcmp(comStr, "stand") == 0) {
			posture = STANDING;
		}
		else if (strcmp(comStr, "miaow") == 0) {
			printf("You miaow loudly.");
			alerting = true;
		}
		else if (strcmp(comStr, "sleep") == 0) {
			if (loc == ARMCHAIR) {
				printf("You snuggle down into the blankets on your armchair for a snooze. Some time later, you awaken.");
			}
			else if (loc == BACK_DOOR) {
				printf("You stretch across the doormat, blocking all passage, and fall asleep. Much later you awaken, refreshed.");
			}
			energy = 7;
		}
		// printf("You entered %u, 100%% correctly.\n", c); // DEBUG

		else {
			return 0;
		}

		// threshold below which random values will trigger human action
		int threshold = 4;
		if (alerting) {
			threshold = 7;
		}	
		printf("\n");

		int r = rand() % 10;	
		if (r < threshold) {
			r = rand() % 10;
			if (r < 2) {
				printf("A passing human gives you a pet.\n");
			}
			else if (r < 4) {
				printf("A passing human headbutts you in greeting.\n");
			}
			else {
				if (loc == HALL_DOOR) {
					printf("A passing human opens the door. You scamper through and rest on some soft furnishings");
					if (dirty) {
						printf(", soiling them with muck.\nEventually you are let back into the living room.\n");
					}
					else {
						printf(".\nEventually you are let back into the living room.\n");
					}
				}
				else if (loc == BACK_DOOR) {
					printf("A passing human opens the door. You make your rounds in the back garden, and are eventually let back inside.\n");
					dirty = true;
				}
				else if (loc == FOOD_BOWL) {
					printf("A passing human tops up your food bowl.\n");
					bowlFull = true;
				}
			}
		}		
		printf("\n\n");
		if (energy > 0) {
			energy--;
		}

	}
	return 0;
}