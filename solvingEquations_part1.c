#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL, malloc, free */
#include <string.h> /* strcpy */
#include <ctype.h>  /* isspace, isdigit, isapotEqha, isalnum */
#include <assert.h> /* assert */
#include "scanner.h"
#include "evalExp.h"
#include "recognizeExp.h"

/* to do:
 * - variables with multiple letters
 * - make acceptFactor
 */


int valueIdentifier(List *potEq, char *c) {
   if (*potEq != NULL && (*potEq)->tt == Identifier) {
     c = ((*potEq)->t).identifier;
     *potEq = (*potEq)->next;
     return 1;
   }
   return 0;
 }

int differentIdentifier (char *s, char *variable) {
   printf("we used differentIdentifier\n\n");
   printf("%s\n",&variable);
   printf("%s\n",&s);
   if (*variable == 0) {
     printf("We encountered the first identifier\n\n");
     *variable = *s;
   } else if (*s == *variable) {
     printf("this identifier is same as the first one we encountered\n\n");

          return 0;
   }
   return 1; // When *variable == NULL or *variable != *s, they are not the same identifiers
 }

int isIdentifier (List *potEq, char *variable, int *var) {
  printf("we used isIdentifier\n\n");
  int i = 0;
  char s[100];
  if( valueIdentifier(potEq, &s[i]) ){
    printf("This is an identifier\n\n");
    do{
      i++;
    } while ( valueIdentifier(potEq, &s[i]) );
    s[i] = '\0';
    *var += differentIdentifier(s, variable);
    printf("%d\n\n", *var );
    return 1;
  }
  return 0;
}

// Returns 1 when 1) there is no power (^) or 2) if there is a valid power
int hasValidPower (List *potEq, int *maxDeg) {
  double degree;
  if ( acceptCharacter(potEq,'^') ) {
    printf("Power Detected\n\n");
	  if ( valueNumber(potEq, &degree) ) {
      printf("Has a power of %d\n\n",(int) degree );
      if ((int) degree > *maxDeg){
        *maxDeg = (int) degree;
        printf("maxDegree == %d\n\n",*maxDeg);
      }
	  } else {
      printf("Power is not valid\n\n");
		return 0;
	  }
  }
  return 1;
}

int isTerm (List *potEq, int *var, int *maxDeg, char *variable) {
  if ( !acceptNumber(potEq) ) {
    if ( !isIdentifier(potEq, variable, var) ) {
      return 0;
    } else {
      if ( !hasValidPower(potEq, maxDeg) ) return 0;
    }
  } else {
	  if ( isIdentifier(potEq, variable, var) ) {
	    if ( !hasValidPower(potEq, maxDeg) ) return 0;
    }
  }
  return 1;
}

int isExpression (List *potEq, int *var, int *maxDeg, char *variable) {
  acceptCharacter(potEq,'-');
  if ( !isTerm(potEq, var, maxDeg, variable) ) {
    printf("is not term\n\n");
    return 0;
  }
  while ( acceptCharacter(potEq,'+') || acceptCharacter(potEq,'-') ) {
    printf("+ or - is read\n\n" );
    if ( !isTerm(potEq, var, maxDeg, variable) ) {
      printf("is not term 2\n\n");
      return 0;
    }
  } /* no + or -, so we reached the end of the expression */
  return 1;
}

// Recognizer function.
int isEquation(List *potEq, int *var, int *maxDeg) {
  char variable = 0;
  if ( !isExpression(potEq, var, maxDeg, &variable) ) {
    printf("First part of isEquation\n\n" );
    return 0;
  }
  if ( !acceptCharacter(potEq,'=') ) {
    printf("Second part of isEquation\n\n" );
    return 0;
  }
  if ( !isExpression(potEq, var, maxDeg, &variable) ) {
    printf("Third part of isEquation\n\n" );
    return 0;
  }
  if ( acceptCharacter(potEq,'=') ) {
      printf("Fourth part of isEquation\n\n");
     return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
	printf("give an equation: ");
	char *s = readInput();
	int variablecount = 0;
	int maxDegree = 0;

	while (s[0] != '!') {
		List potentialEquation = tokenList(s);
		if (isEquation(&potentialEquation, &variablecount, &maxDegree)) {
			printf("\nthis is an equation");
			if (variablecount == 1) { // variable undefined
				printf(" in 1 variable of degree %d\n\n", maxDegree); // degree undefined
			} else if (variablecount > 1) {
				printf(", but not in 1 variable\n\n");
			} else {
        printf(", but something went wrong in counting variables\n\n");
      }
		} else {
			printf("this is not an equation\n\n");
		}
		free(s);
		freeTokenList(potentialEquation);
    variablecount = 0;
		printf("give an equation: ");
		s = readInput();
	}
	printf("good bye");

	return 0;
}
