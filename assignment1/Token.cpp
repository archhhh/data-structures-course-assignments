//
// Token.cpp - Version 1.0
//
// This file is created by Tsz-Chiu Au on 9/24/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "Token.h"

using namespace std;

Token::Token(string s) {
  if (s == "+") {
    _type = Token::OPERATOR_TOKEN;
    _operator = Token::ADDITION_OPERATOR;
  } else
  if (s == "-") {
    _type = Token::OPERATOR_TOKEN;
    _operator = Token::SUBTRACTION_OPERATOR;
  } else
  if (s == "*") {
    _type = Token::OPERATOR_TOKEN;
    _operator = Token::MULTIPLICATION_OPERATOR;
  } else
  if (s == "/") {
    _type = Token::OPERATOR_TOKEN;
    _operator = Token::DIVISION_OPERATOR;
  } else
  if (s == "(") {
    _type = Token::OPERATOR_TOKEN;
    _operator = Token::OPEN_PARENTHESIS_OPERATOR;
  } else
  if (s == ")") {
    _type = Token::OPERATOR_TOKEN;
    _operator = Token::CLOSE_PARENTHESIS_OPERATOR;
  } else
  if (('0' <= s[0] && s[0] <= '9') || (s[0] == '-')) {
    _type = Token::CONSTANT_TOKEN;
    _constant = atoi(s.c_str());
  } else {
    throw runtime_error("Unknown token");
  }
}

Token::Token(int c) {
  _type = Token::CONSTANT_TOKEN;
  _constant = c;
}

bool Token::operator==(const Token& token) const {
  if (_type != token._type) return false;
  switch(_type) {
    case Token::CONSTANT_TOKEN:
      return _constant == token._constant;
    case Token::OPERATOR_TOKEN:
      return _operator == token._operator;
  }
}

ostream& operator<< (ostream &out, const Token &token) {
  switch(token._type) {
    case Token::CONSTANT_TOKEN:
      out << token._constant;
      break;
    case Token::OPERATOR_TOKEN:
      out << token._operator;
      break;
  }
  return out;
}

ostream& operator<< (ostream &out, const Token::Operator &token) {
  switch(token) {
    case Token::ADDITION_OPERATOR:
      out << "+";
      break;
    case Token::SUBTRACTION_OPERATOR:
      out << "-";
      break;
    case Token::MULTIPLICATION_OPERATOR:
      out << "*";
      break;
    case Token::DIVISION_OPERATOR:
      out << "/";
      break;
    case Token::OPEN_PARENTHESIS_OPERATOR:
      out << "(";
      break;
    case Token::CLOSE_PARENTHESIS_OPERATOR:
      out << ")";
      break;
  }
  return out;
}


