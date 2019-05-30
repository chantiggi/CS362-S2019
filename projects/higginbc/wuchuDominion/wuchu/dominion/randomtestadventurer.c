/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Course: CS 362 - Software Engineering II
 * Section: 400 (Spring 2019)
 * Assignment 4 - Random Tester
 * Date: 17 May 2019
*/

//Random Tester for Adventurer card

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
	printf("\n**********************************************\n");
	printf("***** BEGIN TEST: Adventurer Card Effect *****\n");
	printf("**********************************************\n");

	int result;

	/* Initialize the known starting state of the game */
	/* Note that these are variables that are not used directly in the card
	 * effect for the Village card and therefore do not necessarily need
	 * to be randomized */
	int kingdomCards[10] = {adventurer, smithy, minion, salvager, sea_hag, 
				great_hall, feast, mine, village, ambassador};
	int randomSeed = 2500;
	int card = adventurer;
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
	int test1Fails;	// # cards in hand
	int test2Fails;	// # cards in deck+discard
	int test3Fails;	// total # cards
	int test4Fails;	// # cards in played
	int test5Fails;	// function returning 0


	// variables to hold # failures for each test type (total)
	int totTest1Fails = 0;	// # cards in hand
	int totTest2Fails = 0;	// # cards in deck+discard
	int totTest3Fails = 0;	// total # cards
	int totTest4Fails = 0;	// # cards in played
	int totTest5Fails = 0;	// function returning 0


	// loop through all possible numbers of players (2, 3, 4), performing several random tests for each
	for (int p = 2; p < 5; p++)
	{
		// set all to 0 for this # players
		test1Fails = 0;	// # cards in hand
		test2Fails = 0;	// # cards in deck+discard
		test3Fails = 0; // total # cards
		test4Fails = 0;	// # cards in played
		test5Fails = 0;	// function returning 0

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
		
			// Test 1: Check # cards in hand - should be +1 since player draws until they get 2 treasure cards
			// then discards all other cards turned over into discard PLUS discards Adventurer card
			test1Fails += assertTrue("+2/-1 = +1 cards in hand", begState.handCount[currentPlayer] + 1, 
																endState.handCount[currentPlayer]);
			// Test 2: Check # cards in discard+deck - should be -2 since player has now drawn 2 treasure
			// cards from some combo of deck and discard piles (if discard needed to be shuffled)
			test2Fails += assertTrue("-2 cards in deck+discard", (begState.deckCount[currentPlayer]
																+ begState.discardCount[currentPlayer] - 2),
																(endState.deckCount[currentPlayer]
																+ endState.discardCount[currentPlayer]));
			// Test 3: Check total # cards - should be -1 from playing adventurer card
			test3Fails += assertTrue("correct total # cards", (begState.handCount[currentPlayer]
																+ begState.deckCount[currentPlayer]
																+ begState.discardCount[currentPlayer] - 1),
																(endState.handCount[currentPlayer]
																 + endState.deckCount[currentPlayer]
																 + endState.discardCount[currentPlayer]));
			// Test 4: Check total # played cards - should be +1 from playing adventurer
			test4Fails += assertTrue("+1 total # played cards", begState.playedCardCount + 1, 
																endState.playedCardCount);
			// Test 5: Ensure function returns 0 for successful completion of the cardEffect
			test5Fails += assertTrue("cardEffect returns 0", 0, result);

			// move to next player
			endTurn(&endState);

			// Copy over the ending state of this turn to the begState for comparison on next round
			memcpy(&begState, &endState, sizeof(struct gameState));
		
			printf("\n");
		}

		printf("Failures for %d Players:\n", numPlayers);

		printf("Test 1 (# Hand Cards):\t\t\t%d\n", test1Fails);
		printf("Test 2 (# Deck+Discard Cards):\t%d\n", test2Fails);
		printf("Test 3 (total # cards):\t\t\t%d\n", test3Fails);
		printf("Test 4 (# Played Cards):\t\t%d\n", test4Fails);
		printf("Test 5 (returning 0):\t\t\t%d\n", test5Fails);

		totTest1Fails += test1Fails;	// # cards in hand
		totTest2Fails += test2Fails;	// # cards in deck+discard
		totTest3Fails += test3Fails;	// total # cards
		totTest4Fails += test4Fails;	// # cards in played
		totTest5Fails += test5Fails;	// function returning 0
	}

	printf("\nTotal # Failures:\n");

	printf("Test 1 (# Hand Cards):\t\t\t%d\n", totTest1Fails);
	printf("Test 2 (# Deck+Discard Cards):\t\t%d\n", totTest2Fails);
	printf("Test 3 (total # cards):\t\t\t%d\n", totTest3Fails);
	printf("Test 4 (# Played Cards):\t\t%d\n", totTest4Fails);
	printf("Test 5 (returning 0):\t\t\t%d\n\n", totTest5Fails);

	printf("********************************************\n");
	printf("***** END TEST: Adventurer Card Effect *****\n");
	printf("********************************************\n");

	return 0;
}
