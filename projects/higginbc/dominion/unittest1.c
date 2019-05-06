/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS362 - Software Engineering II
 * Assignment 3 - Unit Testing
 * Date: 5 May 2019
*/

/* Unit Test for refactored minion effect function */

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

	/* Initialize other misc variables for use in cardEffect function, etc */
	int currentPlayer = 0;
	int card = minion;
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int *bonus = NULL;

	initializeGame(numPlayers, kingdomCards, randomSeed, &begState);
	begState.coins = 0;	//initialize coins to 0
	// Copy over the starting state of the game to the ending state for comparison of values
	// after the card effect takes place
	memcpy(&endState, &begState, sizeof(struct gameState));
	
	printf("\n****************************************\n");
	printf("***** BEGIN TEST: Minion Unit Test *****\n");
	printf("****************************************\n");

	// Call cardEffect function	
	result = cardEffect(card, choice1, choice2, choice3, &endState, handPos, bonus);
	// Check # actions - should be +1 based on minion effect
	assertTrue("+1 actions", begState.numActions + 1, endState.numActions);


	/******* Test based on Choice #1 to receive 2 coins *******/
	// Note Choice #2 would be implemented in a separate unit test
	assertTrue("+2 coins", begState.coins + 2, endState.coins);
	// Check # cards in hand - should be -1 from playing/discarding minion
	assertTrue("-1 hand cards", begState.handCount[currentPlayer] - 1, endState.handCount[currentPlayer]);
	// Check # discards - should be same since nothing was added to discard pile
	assertTrue("same # discards", begState.discardCount[currentPlayer], endState.discardCount[currentPlayer]);	
	// Check # cards in deck - should be same since nothing new was drawn
	assertTrue("same # deck cards", begState.deckCount[currentPlayer], endState.deckCount[currentPlayer]);
	// Check total # cards - should be -1 from playing this card into played pile
	assertTrue("-1 total cards from playing minion",
						(begState.handCount[currentPlayer]
						+ begState.deckCount[currentPlayer]
						+ begState.discardCount[currentPlayer] - 1),
						(endState.handCount[currentPlayer]
						+ endState.deckCount[currentPlayer]
						+ endState.discardCount[currentPlayer]));
	// Check total # played cards - should be +1 from playing minion
	assertTrue("+1 total # played cards", begState.playedCardCount + 1, endState.playedCardCount);
	// Ensure function returns 0 for successful completion of the cardEffect
	assertTrue("cardEffect returns 0", 0, result);
	
	printf("**************************************\n");
	printf("***** END TEST: Minion Unit Test *****\n");
	printf("**************************************\n");

	return 0;
}
