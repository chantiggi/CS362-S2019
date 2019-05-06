/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS362 - Software Engineering II
 * Assignment 3 - Unit Testing
 * Date: 5 May 2019
*/

/* Unit Test for updateCoins() function */

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
	int result;

	/* Initialize the known starting state of the game */
	int numPlayers = 2;
	int kingdomCards[10] = {adventurer, smithy, minion, salvager, sea_hag, 
				council_room, feast, mine, village, ambassador};
	int randomSeed = 2500;
	struct gameState begState, endState;
	int currentPlayer = 0;

	initializeGame(numPlayers, kingdomCards, randomSeed, &begState);
	// Copy over the starting state of the game to the ending state for comparison of values
	// after the card effect takes place
	memcpy(&endState, &begState, sizeof(struct gameState));
	
	printf("\n***********************************************\n");
	printf("***** BEGIN TEST: updateCoins() Unit Test *****\n");
	printf("***********************************************\n");

	// Call cardEffect function	
	result = updateCoins(currentPlayer, &endState, 0);

	int numCoins = 0;
	int numHandCards = endState.handCount[currentPlayer];

	for (int i = 0; i < numHandCards; i++)
	{
		if (endState.hand[currentPlayer][i] == copper)
		{
			numCoins += 1;
		}
		else if (endState.hand[currentPlayer][i] == silver)
		{
			numCoins += 2;
		}
		else if (endState.hand[currentPlayer][i] == gold)
		{
			numCoins += 3;
		}
	}

	// Ensure the number of coins manually calculated matches the amount in the game state
	assertTrue("correct # coins", numCoins, endState.coins);

	// Ensure function returns 0 for successful completion of the cardEffect
	assertTrue("updateCoins returns 0", 0, result);
	
	printf("*********************************************\n");
	printf("***** END TEST: updateCoins() Unit Test *****\n");
	printf("*********************************************\n");

	return 0;
}
