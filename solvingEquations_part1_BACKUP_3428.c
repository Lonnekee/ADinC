#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL, malloc, free */
#include <string.h> /* strcpy */
#include <ctype.h>  /* isspace, isdigit, isalpha, isalnum */
#include <assert.h> /* assert */
#include "scanner.h"

/* to do:
 * - variables with multiple letters
 * - make acceptFactor
 */

int valueIdentifier (List *potEq, int *var, char *variable) {
  if (*lp != NULL && (*lp)->tt == Identifier ) {
	*variable = ((*potEq)->t).(*identifier);
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int sameIdentifier (char *s, char *variable) {
  if (*variable == NULL) {
	*variable == *s;
  } else if (*variable == *s) {
    int i = 0, maxIdent = strlen(variable);
    while(i < maxIdent){
      if(*s[i] == variable[i] && i == maxIdent - 1){
        return 1;
      }
  }
  return 0; // When *variable == NULL or *variable != *s, they are not the same identifiers
}

int acceptFactor(List *lp) {
  // to do: valueIdentifier, sameIdentifier, acceptFactor
}

int isTerm (List *potEq, int *var, int *maxDeg, char *variable) {
  if ( acceptNumber(...) ) {
	  acceptFactor(...); //value of acceptFactor is not used?
  } else if (acceptFactor(...) ) {
	  return 1;
  }
  return 0;
}

int isExpression(List *potEq, int *var, int *maxDeg, char *variable) {
  if ( !isTerm(potEq, var, maxDeg, variable) ) {
    return 0;
  }
  while ( acceptCharacter(potEq,'+') || acceptCharacter(potEq,'-') ) {
    if ( !isTerm(potEq, var, maxDeg, variable) ) {
      return 0;
    }
  } /* no + or -, so we reached the end of the expression */
  return 1;
}

// Recognizer function.
int isEquation(List *potEq, int *var, int *maxDeg) {
  char *variable = NULL;
<<<<<<< HEAD
  if ( !isExpression(potEq, var, maxDeg, variable) ) {
    return 0; 
=======
  if ( !isExpression(potEq, var, deg, variable) ) {
    return 0;
>>>>>>> 8a93dcbcd65304e9c3125b69f334a12bbf3cf306
  }
  if ( !acceptCharacter(potEq,'=') ) {
	return 0;
  }
  if ( !=isExpression(potEq, var, maxDeg, variable) ) {
	return 0;
  }
  if ( acceptCharacter(potEq,'=') ) {
	return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
	printf("give an equation: ");
	char *s = readInput();
<<<<<<< HEAD
	int variable = NULL;
	int maxDegree = 0;
	
	while (s[0] != '!') {
		List potentialEquation = tokenList(s);
		if (isEquation(potentialEquation, variable, maxDegree)) {
			printf("\nthis is an equation");
=======
	int variable, degree;

	while (s[0] != '!') {
		List potentialEquation = tokenList(s);
		if (isEquation(potentialEquation, variable, degree)) {
			printf("this is an equation");
>>>>>>> 8a93dcbcd65304e9c3125b69f334a12bbf3cf306
			if (variable == 1) { // variable undefined
				printf(" in 1 variable of degree %d\n\n", maxDegree); // degree undefined
			} else {
				printf(", but not in 1 variable");
			}
		} else {
			printf("this is not an equation\n\n");
		}
		free(s);
		freeTokenList(potentialEquation);
		printf("give an equation: ");
		s = readInput();
	}
	printf("good bye");

	return 0;
}
