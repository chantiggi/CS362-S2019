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

cardtest1: cardtest1.c dominion.o
	gcc -o cardtest1 -ftest-coverage -fprofile-arcs cardtest1.c -g dominion.o rngs.o ${CFLAGS}

cardtest2: cardtest2.c dominion.o
	gcc -o cardtest2 -ftest-coverage -fprofile-arcs cardtest2.c -g dominion.o rngs.o ${CFLAGS}

cardtest3: cardtest3.c dominion.o
	gcc -o cardtest3 -ftest-coverage -fprofile-arcs cardtest3.c -g dominion.o rngs.o ${CFLAGS}

cardtest4: cardtest4.c dominion.o
	gcc -o cardtest4 -ftest-coverage -fprofile-arcs cardtest4.c -g dominion.o rngs.o ${CFLAGS}

randomtestadventurer: randomtestadventurer.c dominion.o
	gcc -o randomtestadventurer -ftest-coverage -fprofile-arcs randomtestadventurer.c -g dominion.o rngs.o ${CFLAGS}

randomtestcard1: randomtestcard1.c dominion.o
	gcc -o randomtestcard1 -ftest-coverage -fprofile-arcs randomtestcard1.c -g dominion.o rngs.o ${CFLAGS}

randomtestcard2: randomtestcard2.c dominion.o
	gcc -o randomtestcard2 -ftest-coverage -fprofile-arcs randomtestcard2.c -g dominion.o rngs.o ${CFLAGS}


cardtests: cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2
	./cardtest1 &> cardtestresults.out
	./randomtestadventurer >> cardtestresults.out
	./cardtest2 >> cardtestresults.out
	./cardtest3 >> cardtestresults.out
	./randomtestcard1 >> cardtestresults.out
	./cardtest4 >> cardtestresults.out
	./randomtestcard2 >> cardtestresults.out
	gcov -f dominion.c >> cardtestresults.out
	cat dominion.c.gcov >> cardtestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o  playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2
