/*
 * Name: Chantel Higginbotham (higginbc@oregonstate.edu)
 * Class: CS362 - Software Engineering II
 * Section: 400 (Spring 2019)
 * Assignment: Random Testing Quiz
 * Date: 6 May 2019
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // need to cover the range of ASCII values covered in the testme() function below
    // minimum of these is 32 ( space ) and maximum is 125 ( } )
    char testChar = (char)(rand() % (125 - 32 + 1)) + 32;
    
    return testChar;
}

char *inputString()
{
    // need to cover the range of ASCII values that include letters r, e, s, e, t
    // r = 114, e = 101, s = 115, e = 101, t = 116
    // minimum of these is 101 ( e ) and maximum is 116 ( t )
    char testString[6];

    for (int i = 0; i < 5; i++)
    {
      // rand() by the difference b/w 116 and 101, but add 1 to ensure this is inclusive
      // of ALL 16 characters in the range
      testString[i] = (char)((rand() % (116 - 101 + 1)) + 101);
    }
    // append the null terminator to the end of the string
    testString[5] = '\0';

    char *randomString = testString;
    return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;  // [ = 91 
    if (c == '(' && state == 1) state = 2;  // ( = 40
    if (c == '{' && state == 2) state = 3;  // { = 123
    if (c == ' '&& state == 3) state = 4;   // ' ' = 32
    if (c == 'a' && state == 4) state = 5;  // a = 97
    if (c == 'x' && state == 5) state = 6;  // x = 120
    if (c == '}' && state == 6) state = 7;  // } = 125
    if (c == ')' && state == 7) state = 8;  // ) = 41
    if (c == ']' && state == 8) state = 9;  // ] = 93
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
