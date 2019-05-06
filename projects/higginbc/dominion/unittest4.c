/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS362 - Software Engineering II
 * Assignment 3 - Unit Testing
 * Date: 5 May 2019
*/

/* Unit Test for whoseTurn() function */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

void assertTrue(char* testName, int expected, int actual)
{
	printf("TEST %s (Expected = %d // Actual = %d):  ", testName, expected, actual);

	if (expected == actual) { printf("PASSED\n"); }
	else { printf("FAILED\n"); }
}	

int main(int argc, char** argv)
{
	/* Initialize the known starting state of the game */
	int numPlayers = 4;
	int kingdomCards[10] = {adventurer, smithy, minion, salvager, sea_hag, 
				council_room, feast, mine, village, ambassador};
	int randomSeed = 2500;
	struct gameState begState, endState;

	initializeGame(numPlayers, kingdomCards, randomSeed, &begState);
	// Copy over the starting state of the game to the ending state for comparison of values
	// after the card effect takes place
	memcpy(&endState, &begState, sizeof(struct gameState));
	
	printf("\n*********************************************\n");
	printf("***** BEGIN TEST: whoseTurn() Unit Test *****\n");
	printf("*********************************************\n");

	int playerNum;

	for (int i = 0; i < numPlayers*2; i++)
	{
		printf("--SUBTRIAL %d--\n", i+1);
		playerNum = whoseTurn(&endState);
		assertTrue("whoseTurn() returns correct player #", i % numPlayers, playerNum);
		endTurn(&endState);	// end current player turn and move to next player
	}
	
	printf("*******************************************\n");
	printf("***** END TEST: whoseTurn() Unit Test *****\n");
	printf("*******************************************\n");

	return 0;
}
