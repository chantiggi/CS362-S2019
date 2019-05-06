/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS362 - Software Engineering II
 * Assignment 3 - Unit Testing
 * Date: 5 May 2019
*/

/* Unit Test for refactored salvager effect function */

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
	int card = salvager;
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
	
	printf("\n******************************************\n");
	printf("***** BEGIN TEST: Salvager Unit Test *****\n");
	printf("******************************************\n");

	printf("-----TEST #1: Player chooses NOT to trash a card (choice1 == 0)-----\n");
	// Call cardEffect function	
	result = cardEffect(card, choice1, choice2, choice3, &endState, handPos, bonus);
	// Check # buys - should be +1 based on salvager effect
	assertTrue("+1 buys", begState.numBuys + 1, endState.numBuys);
	// Check # cards in hand - should be -2 after trashing the chosen card
	assertTrue("-1 to handCount from discarding",
				begState.handCount[currentPlayer] - 1,
				endState.handCount[currentPlayer]);
	// Check total # cards - should be the same since player has chosen not to trash any
	assertTrue("-1 total cards from playing salvager",
						(begState.handCount[currentPlayer]
						+ begState.deckCount[currentPlayer]
						+ begState.discardCount[currentPlayer] - 1),
						(endState.handCount[currentPlayer]
						+ endState.deckCount[currentPlayer]
						+ endState.discardCount[currentPlayer]));
	// Check # coins - should be the same since player has chosen not to trash any cards in exchange
	// for coins
	assertTrue("same # coins", begState.coins, endState.coins);
	// Check total # played cards - should be +1 from playing salvager
	assertTrue("+1 total # played cards", begState.playedCardCount + 1, endState.playedCardCount);
	// Ensure function returns 0 for successful completion of the cardEffect
	assertTrue("cardEffect returns 0", 0, result);
	printf("-----END TEST #1-----\n");


	printf("\n-----TEST #2: Player chooses to trash a card-----\n");
	// Run a SEPARATE test for the current player choosing to discard EACH card in their
	// hand to get decent coverage of different coin/cost ranges, etc
	int numCardsInHand = begState.handCount[currentPlayer];
	for (int i = 1; i < numCardsInHand; i++)
	{
		// Reset endState back to begState and set choice1 equal to i
		memcpy(&endState, &begState, sizeof(struct gameState));
		choice1 = i;
		int cardChoice = handCard(choice1, &endState);
		
		printf("--SUB-TRIAL %d: choice1 = %d // card enum value = %d--\n", i, choice1, cardChoice);
		// Call cardEffect function	
		result = cardEffect(card, choice1, choice2, choice3, &endState, handPos, bonus);
		// Check # buys - should be +1 based on salvager effect
		assertTrue("+1 buys", begState.numBuys + 1, endState.numBuys);
		// Check # cards in hand - should be -2 after trashing the chosen card
		assertTrue("-1/-1 = -2 to handCount from trashing + discarding one",
				begState.handCount[currentPlayer] - 1 - 1,
				endState.handCount[currentPlayer]);
		// Check total # cards - should be -1 after trashing the chosen card
		assertTrue("-2 total cards from trashing one + discarding salvager",
							(begState.handCount[currentPlayer]
							+ begState.deckCount[currentPlayer]
							+ begState.discardCount[currentPlayer] - 2),
							(endState.handCount[currentPlayer]
							+ endState.deckCount[currentPlayer]
							+ endState.discardCount[currentPlayer]));
		// Check # coins - should be increased since we trashed a card in exchange for coins
		assertTrue("+[some #] coins", begState.coins + getCost(cardChoice), endState.coins);
		// Check total # played cards - should be +1 from playing salvager
		assertTrue("+1 total # played cards", begState.playedCardCount + 1, endState.playedCardCount);
		// Ensure function returns 0 for successful completion of the cardEffect
		assertTrue("cardEffect returns 0", 0, result);
		printf("--END SUB-TRIAL %d--\n\n", i);
	}
	printf("-----END TEST #2-----\n");
	
	printf("****************************************\n");
	printf("***** END TEST: Salvager Unit Test *****\n");
	printf("****************************************\n");

	return 0;
}
