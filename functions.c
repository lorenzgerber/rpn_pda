/*
 * These functions were implemented for an assignment in course DV2:
 * Algorithms and problemsolving 7.5 p, 5DV169
 */



/*
 * Function that checks for operator. If the provided argument
 * is one of the four base operators, the function returns 1
 */
int isOperator(int toCheck){
    if(toCheck == 42 || toCheck == 43 || toCheck == 45 || toCheck == 47)
        return 1;
    return 0;
}

/*
 * Function that checks for a blank.
 */
int isBlank(int toCheck){
    if(toCheck == 32)
        return 1;
    return 0;

}

/*
 * Function used as epsilon condition in transitions
 */
int isEpsilon(int notUsed){
    return 1;
}

/*
 * Function that returns the argument
 */
int pushInput(int notUsed){
    return 256;
}

/*
 * Function to check if input is empty/used up
 */
int isTerminal(int input){
    if(input == 4)
        return 1;
    return 0;
}


/*
 * Function that returns the int value ofa a '$' char
 */
int dollarSymbol(int notUsed){
    return 36;
}

/*
 * Function that checks for a '$' char
 */
int isDollarSymbol(int toCheck){
    if(toCheck == 36)
        return 1;
    return 0;
}

/*
 * Function that returns the int value of a blank char
 */
int blankChar(int notUsed){
    return 32;
}

/*
 * Function that checks for a '(' char
 */
int isOpeningBracket(int toCheck){
    if(toCheck == 40)
        return 1;
    return 0;
}


/*
 * Function that checks for a ')' char
 */
int isClosingBracket(int toCheck){
    if(toCheck == 41)
        return 1;
    return 0;
}

/*
 * Function that returns the int value ofa a '(' char
 */
int openingBracket(int notUsed){
    return 40;
}