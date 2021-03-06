CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: unittest1.c dominion.o
	gcc -o unittest1 -ftest-coverage -fprofile-arcs unittest1.c -g dominion.o rngs.o ${CFLAGS}

unittest2: unittest2.c dominion.o
	gcc -o unittest2 -ftest-coverage -fprofile-arcs unittest2.c -g dominion.o rngs.o ${CFLAGS}

unittest3: unittest3.c dominion.o
	gcc -o unittest3 -ftest-coverage -fprofile-arcs unittest3.c -g dominion.o rngs.o ${CFLAGS}

unittest4: unittest4.c dominion.o
	gcc -o unittest4 -ftest-coverage -fprofile-arcs unittest4.c -g dominion.o rngs.o ${CFLAGS}

cardtest1: cardtest1.c dominion.o
	gcc -o cardtest1 -ftest-coverage -fprofile-arcs cardtest1.c -g dominion.o rngs.o ${CFLAGS}

cardtest2: cardtest2.c dominion.o
	gcc -o cardtest2 -ftest-coverage -fprofile-arcs cardtest2.c -g dominion.o rngs.o ${CFLAGS}

cardtest3: cardtest3.c dominion.o
	gcc -o cardtest3 -ftest-coverage -fprofile-arcs cardtest3.c -g dominion.o rngs.o ${CFLAGS}

cardtest4: cardtest4.c dominion.o
	gcc -o cardtest4 -ftest-coverage -fprofile-arcs cardtest4.c -g dominion.o rngs.o ${CFLAGS}

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

