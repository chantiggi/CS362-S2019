/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS362 - Software Engineering II
 * Assignment 3 - Unit Testing
 * Date: 5 May 2019
*/

/* Card Test for Great Hall effect */

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
				great_hall, feast, mine, village, ambassador};
	int randomSeed = 2500;
	struct gameState begState, endState;

	/* Initialize other misc variables for use in cardEffect function, etc */
	int currentPlayer = 0;
	int card = great_hall;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int *bonus = NULL;

	initializeGame(numPlayers, kingdomCards, randomSeed, &begState);
	begState.coins = 0;	// initialize # coins to 0
	// Copy over the starting state of the game to the ending state for comparison of values
	// after the card effect takes place
	memcpy(&endState, &begState, sizeof(struct gameState));
	
	printf("\n**********************************************\n");
	printf("***** BEGIN TEST: Great Hall Card Effect *****\n");
	printf("**********************************************\n");

	// Call cardEffect function
	result = cardEffect(card, choice1, choice2, choice3, &endState, handPos, bonus);
	// Check # actions - should be +1 based on great_hall card effect
	assertTrue("+1 actions", begState.numActions + 1, endState.numActions);
	
	// Check # cards in hand - should be same since player draws 1 and discards 1
	assertTrue("same # cards in hand", begState.handCount[currentPlayer], 
						endState.handCount[currentPlayer]);
	// Check # cards in discard - should be unchanged since only card played was great hall which
	// was put into the played pile, not the player's discard pile
	assertTrue("same # cards in discard", begState.discardCount[currentPlayer],
						endState.discardCount[currentPlayer]);
	// Check # cards in deck to draw from - should be -1 since player started off
	// with well over 1 card in the deck and drew 1 from the deck after playing great hall card
	assertTrue("-1 cards in deck", begState.deckCount[currentPlayer] - 1,
						endState.deckCount[currentPlayer]);
	// Check total # played cards - should be +1 from playing great hall
	assertTrue("+1 total # played cards", begState.playedCardCount + 1, endState.playedCardCount);
	// Ensure function returns 0 for successful completion of the cardEffect
	assertTrue("cardEffect returns 0", 0, result);

	printf("********************************************\n");
	printf("***** END TEST: Great Hall Card Effect *****\n");
	printf("********************************************\n");

	return 0;
}
