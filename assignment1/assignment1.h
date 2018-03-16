//
// assignment1.h - Version 1.0
//
// This file is created by Tsz-Chiu Au on 9/24/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#ifndef ASSIGNMENT1_ASSIGNMENT1_H
#define ASSIGNMENT1_ASSIGNMENT1_H

#include <vector>
#include "Token.h"

using namespace std;


/*
 * Return the priority of an operator. The token must
 * be an operator; otherwise, it will throw an exception.
 * The only operators this function can handle are '+', '-',
 * '*', '/', and '('; For other operators, this function will
 * throw an exception. The higher the priority of an operator is,
 * the smaller the number this function returns.
 *
 * token - the token of the operator.
 * return the priority of the operator.
 */
int getPriority(Token token);

/*
 * This function is the same as getPriority() except
 * that it returns the in-stack priority, which gives
 * '(' a very low priority.
 *
 * token - the token of the operator.
 * return the in-stack priority of the operator.
 */
int getInStackPriority(Token token);


/*
 * Convert an expression in infix notation into an expression in postfix
 * notation. The expressions are stored as a vector of tokens.
 *
 * expression - the vector of tokens of the expression in infix notation
 * return the vector of tokens of the expression in postfix notation
 */
vector<Token> postfix(const vector<Token>& expression);

/*
 * Evaluate an expression in postfix notation.
 *
 * expression - the vector of tokens of the expression in postfix notation
 * return the value of the expression
 */
int eval(const vector<Token>& expression);


#endif //ASSIGNMENT1_ASSIGNMENT1_H
