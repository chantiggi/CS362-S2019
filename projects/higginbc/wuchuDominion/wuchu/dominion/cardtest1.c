/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS362 - Software Engineering II
 * Assignment 3 - Unit Testing
 * Date: 5 May 2019
*/

/* Card Test for Adventurer effect */

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
	int card = adventurer;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int *bonus = NULL;

	initializeGame(numPlayers, kingdomCards, randomSeed, &begState);
	// Copy over the starting state of the game to the ending state for comparison of values
	// after the card effect takes place
	memcpy(&endState, &begState, sizeof(struct gameState));
	
	printf("\n**********************************************\n");
	printf("***** BEGIN TEST: Adventurer Card Effect *****\n");
	printf("**********************************************\n");

	// Call cardEffect function	
	result = cardEffect(card, choice1, choice2, choice3, &endState, handPos, bonus);
	// Check # cards in hand - should be +1 since player draws until they get 2 treasure cards then
	// discards all other cards turned over into the discard pile plus discards the Adventurer card
	assertTrue("+2/-1 = +1 cards in hand", begState.handCount[currentPlayer] + 1, 
						endState.handCount[currentPlayer]);
	// Check # cards in discard + deck - should be -2 since player has now drawn 2 treasure
	// cards from some combination of the deck and discard piles (if the discard needed to be shuffled)
	assertTrue("-2 cards in (deck + discard)", (begState.deckCount[currentPlayer] 
						+ begState.discardCount[currentPlayer] - 2),
						(endState.deckCount[currentPlayer]
						+ endState.discardCount[currentPlayer]));
	// Check total # cards - should be -1 from the player playing the adventurer card
	assertTrue("-1 total cards from playing adventurer", 
						(begState.handCount[currentPlayer]
						+ begState.deckCount[currentPlayer]
						+ begState.discardCount[currentPlayer] - 1),
						(endState.handCount[currentPlayer]
						+ endState.deckCount[currentPlayer]
						+ endState.discardCount[currentPlayer]));
	// Check total # played cards - should be +1 from playing adventurer
	assertTrue("+1 total # played cards", begState.playedCardCount + 1, endState.playedCardCount);
	// Ensure function returns 0 for successful completion of the cardEffect
	assertTrue("cardEffect returns 0", 0, result);	

	printf("********************************************\n");
	printf("***** END TEST: Adventurer Card Effect *****\n");
	printf("********************************************\n");

	return 0;
}
