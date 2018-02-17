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

// Returns 1 when 1) there is no power (^) or 2) if there is a valid power
int hasValidPower (List potEq, int *maxDeg) {
  int degree;
  if ( acceptCharacter(potEq,'^') ) {
	  if ( valueNumber(potEq, &degree) ) {
	    if (degree > *maxDeg) *maxDeg = degree;
	  } else {
		return 0;
	  }
  }
  return 1;
}

int isTerm (List *potEq, int *var, int *maxDeg, char *variable) {
  if ( !acceptNumber(potEq) ) {
    if ( !valueIdentifier(potEq, var) ) {
      return 0;
    } else {
      if ( !hasValidPower(potEq, maxDeg) return 0;
    }
  } else {
	if ( valueIdentifier(potEq, var) ) {
	  if ( !hasValidPower(potEq, maxDeg) ) return 0;
    }
  }
  return 1;
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
  if ( !isExpression(potEq, var, maxDeg, variable) ) {
    return 0; 
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
	int variable = NULL;
	int maxDegree = 0;
	
	while (s[0] != '!') {
		List potentialEquation = tokenList(s);
		if (isEquation(potentialEquation, variable, maxDegree)) {
			printf("\nthis is an equation");
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
