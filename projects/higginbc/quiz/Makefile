CFLAGS= -Wall -fpic -coverage -lm -std=c99

randomtest: testme
	./testme

testme: testme.c
	gcc -o testme -ftest-coverage -fprofile-arcs testme.c -g ${CFLAGS}

clean:
	rm -f testme *.gcno *.gcda *.gcov
