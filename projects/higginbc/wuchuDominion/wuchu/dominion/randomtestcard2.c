/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS 362 - Software Engineering II
 * Section: 400 (Spring 2019)
 * Assignment 4 - Random Tester
 * Date: 17 May 2019
*/

//Random Tester for Village card

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_RANDOM_TESTS 10

int assertTrue(char* testName, int expected, int actual)
{
	printf("TEST %s (Expected = %d // Actual = %d):  ", testName, expected, actual);

	if (expected == actual) { printf("PASSED\n"); return 0; }
	else { printf("FAILED\n"); return 1; }
}	

int main(int argc, char** argv)
{
	printf("\n*******************************************\n");
	printf("***** BEGIN TEST: Village Card Effect *****\n");
	printf("*******************************************\n");

	int result;

	/* Initialize the known starting state of the game */
	/* Note that these are variables that are not used directly in the card
	 * effect for the Village card and therefore do not necessarily need
	 * to be randomized */
	int kingdomCards[10] = {adventurer, smithy, minion, salvager, sea_hag, 
				great_hall, feast, mine, village, ambassador};
	int randomSeed = 2500;
	int card = village;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int *bonus = NULL;

	// declare variables to be randomized for each random test
	int numPlayers;
	int currentPlayer;
	int handPos;
	struct gameState begState, endState;

	// seed random number generator
	srand(time(NULL));

	// variables to hold # failures for each test type (for each # players)
	int test1Fails;	// # actions
	int test2Fails;	// # cards in hand
	int test3Fails;	// # cards in deck
	int test4Fails;	// # cards in discard
	int test5Fails;	// # cards in played
	int test6Fails;	// total # cards
	int test7Fails;	// function returning 0


	// variables to hold # failures for each test type (total)
	int totTest1Fails = 0;	// # actions
	int totTest2Fails = 0;	// # cards in hand
	int totTest3Fails = 0;	// # cards in deck
	int totTest4Fails = 0;	// # cards in discard
	int totTest5Fails = 0;	// # cards in played
	int totTest6Fails = 0;	// total # cards
	int totTest7Fails = 0;	// function returning 0


	// loop through all possible numbers of players (2, 3, 4), performing several random tests for each
	for (int p = 2; p < 5; p++)
	{
		// set all to 0 for this # players
		test1Fails = 0;	// # actions
		test2Fails = 0;	// # cards in hand
		test3Fails = 0;	// # cards in deck
		test4Fails = 0;	// # cards in discard
		test5Fails = 0;	// # cards in played
		test6Fails = 0; // total # cards
		test7Fails = 0;	// function returning 0

		numPlayers = p;
		if ((initializeGame(numPlayers, kingdomCards, randomSeed, &begState)) == -1)
		{
			printf("Error initializing the game\n");
			return 1;
		}

		// Copy over the starting state of the game for this # players to compare values before and
		// after card effect takes place
		memcpy(&endState, &begState, sizeof(struct gameState));

		printf("\n---# Players = %d---\n", numPlayers);
	
		// perform several random tests for each game state
		for (int i = 0; i < NUM_RANDOM_TESTS; i++)
		{
			currentPlayer = whoseTurn(&endState);

			// randomize hand position
			handPos = rand() % endState.handCount[currentPlayer];
		
			// Call cardEffect function
			result = cardEffect(card, choice1, choice2, choice3, &endState, handPos, bonus);
			
			// Test 1: Check # actions - should be +2 based on village card effect
			test1Fails += assertTrue("+2 actions", begState.numActions + 2, endState.numActions);
			// Test 2: Check # cards in hand - should be same since player draws 1 and discards 1
			test2Fails += assertTrue("same # cards in hand", begState.handCount[currentPlayer], 
								endState.handCount[currentPlayer]);
			// Test 3: Check # cards in deck to draw from - should be -1 OR sum of previous discard pile from
			// shuffling (when the player had to draw a new card) -1 from drawing a card
			int expectedDeckCount = begState.deckCount[currentPlayer] - 1;
			if (expectedDeckCount < 0)
			{
				expectedDeckCount = begState.discardCount[currentPlayer] - 1;
			}
			test3Fails += assertTrue("-1 cards in deck OR discard shuffled back into deck", expectedDeckCount,
								endState.deckCount[currentPlayer]);
			// Test 4: Check # cards in discard - should only be changed if the player's deck was empty which
			// would mean they had to shuffle the discard back into the deck leaving the deck at size 0
			int expectedDiscardCount = begState.discardCount[currentPlayer];
			if (begState.deckCount[currentPlayer] - 1 < 0)
			{
				expectedDiscardCount = 0;
			}
			test4Fails += assertTrue("correct # cards in discard", expectedDiscardCount,
								endState.discardCount[currentPlayer]);
			// Test 5: Check total # played cards - should be +1 from playing village
			test5Fails += assertTrue("+1 total # played cards", begState.playedCardCount + 1, 
									endState.playedCardCount);
			// Test 6: Check total # cards - should be -1 from playing village card
			test6Fails += assertTrue("correct total # cards", (begState.handCount[currentPlayer]
																+ begState.deckCount[currentPlayer]
																+ begState.discardCount[currentPlayer] - 1),
																(endState.handCount[currentPlayer]
																 + endState.deckCount[currentPlayer]
																 + endState.discardCount[currentPlayer]));
			// Test 7: Ensure function returns 0 for successful completion of the cardEffect
			test7Fails += assertTrue("cardEffect returns 0", 0, result);

			// move to next player
			endTurn(&endState);

			// Copy over the ending state of this turn to the begState for comparison on next round
			memcpy(&begState, &endState, sizeof(struct gameState));
		
			printf("\n");
		}

		printf("Failures for %d Players:\n", numPlayers);

		printf("Test 1 (# Actions):\t\t\t%d\n", test1Fails);
		printf("Test 2 (# Hand Cards):\t\t%d\n", test2Fails);
		printf("Test 3 (# Deck Cards):\t\t%d\n", test3Fails);
		printf("Test 4 (# Discard Cards):\t%d\n", test4Fails);
		printf("Test 5 (# Played Cards):\t%d\n", test5Fails);
		printf("Test 6 (total # cards):\t\t%d\n", test6Fails);
		printf("Test 7 (returning 0):\t\t%d\n", test7Fails);

		totTest1Fails += test1Fails;	// # actions
		totTest2Fails += test2Fails;	// # cards in hand
		totTest3Fails += test3Fails;	// # cards in deck
		totTest4Fails += test4Fails;	// # cards in discard
		totTest5Fails += test5Fails;	// # cards in played
		totTest6Fails += test6Fails;	// total # cards
		totTest7Fails += test7Fails;	// function returning 0
	}

	printf("\nTotal # Failures:\n");

	printf("Test 1 (# Actions):\t\t\t%d\n", totTest1Fails);
	printf("Test 2 (# Hand Cards):\t\t%d\n", totTest2Fails);
	printf("Test 3 (# Deck Cards):\t\t%d\n", totTest3Fails);
	printf("Test 4 (# Discard Cards):\t%d\n", totTest4Fails);
	printf("Test 5 (# Played Cards):\t%d\n", totTest5Fails);
	printf("Test 6 (total # cards):\t\t%d\n", totTest6Fails);
	printf("Test 7 (returning 0):\t\t%d\n\n", totTest7Fails);

	printf("*****************************************\n");
	printf("***** END TEST: Village Card Effect *****\n");
	printf("*****************************************\n");

	return 0;
}
