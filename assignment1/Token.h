//
// Token.h - Version 1.0
//
// This file is created by Tsz-Chiu Au on 9/24/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#ifndef ASSIGNMENT3_TOKEN_H
#define ASSIGNMENT3_TOKEN_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Token {

public:

  /*
   * The types of tokens.
   */
  enum TokenType { CONSTANT_TOKEN,    // integer constant
                   OPERATOR_TOKEN };  // operator

  /*
   * The operators. Notice that DIVISION_OPERATOR is an integer division.
   */
  enum Operator { ADDITION_OPERATOR,
                  SUBTRACTION_OPERATOR,
                  MULTIPLICATION_OPERATOR,
                  DIVISION_OPERATOR,
                  OPEN_PARENTHESIS_OPERATOR,
                  CLOSE_PARENTHESIS_OPERATOR };

  /*
   * Default constructor that does nothing.
   */
  Token() {}

  /*
   * Construct a token by parsing a string.
   */
  Token(string s);

  /*
   * Construct a constant token of an integer.
   *
   * c - an integer
   */
  Token(int c);

  /*
   * Return the type of this token.
   *
   * return the type of this token
   */
  TokenType getTokenType() const {
    return _type;
  }

  /*
   * Check whether this token is a constant token.
   *
   * return true if this token is a constant token
   */
  bool isConstant() const {
    return _type == CONSTANT_TOKEN;
  }

  /*
   * Check whether this token is an operator token.
   *
   * return true if this token is an operator token
   */
  bool isOperator() const {
    return _type == OPERATOR_TOKEN;
  }

  /*
   * Check whether this token is equal to another token.
   *
   * token - another token
   * return true if this token is equal to another token
   */
  bool operator==(const Token& token) const;

  /*
   * Return the integer value of the constant if this is a constant token.
   *
   * return the integer value of this constant
   */
  int getConstant() const {
    if (_type != CONSTANT_TOKEN) throw runtime_error("Not a constant token.");
    return _constant;
  }

  /*
   * Return the type of the operator if this is an operator token.
   *
   * return the type of the operator of this operator token
   */
  Operator getOperator() const {
    if (_type != OPERATOR_TOKEN) throw runtime_error("Not an operator token.");
    return _operator;
  }

  friend ostream& operator<<(ostream &out, const Token &p);
  friend ostream& operator<<(ostream &out, const Token::Operator &p);

private:

  TokenType _type;
  int _constant;
  Operator _operator;
};

#endif //ASSIGNMENT3_TOKEN_H
