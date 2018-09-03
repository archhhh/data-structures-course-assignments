//
// tokenizer.cpp - Version 1.0
//
// This file is created by Tsz-Chiu Au on 9/24/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#include <vector>
#include <string>
#include <stdexcept>
#include "tokenizer.h"

using namespace std;

bool isOperator(char c) {
  return c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')';
}

bool isNumber(char c) {
  return '0' <= c && c <= '9';
}

bool isInteger(string s) {
  if (s == "") {
    return false;
  } else if (s.size() == 1) {
    return isNumber(s[0]);
  } else {
    if (!isNumber(s[0]) && s[0] != '-') {
      return false;
    }
    for (int i = 1; i < s.size(); i++) {
      if (!isNumber(s[i])) return false;
    }
    return true;
  }
}

vector<string> equation_partition(const string &eqn) {
  enum CharType { EMPTY, INTEGER, OPERATOR, SPACE };

  CharType last_char_type = EMPTY;
  vector<string> partition;
  string tmp_str = "";

  for (string::const_iterator iter = eqn.begin(); iter != eqn.end(); iter++) {
    char c = *iter;
    if (c == ' ') {
      if (last_char_type != SPACE && tmp_str != "") {
        partition.push_back(tmp_str);
        tmp_str = "";
      }
      last_char_type = SPACE;
      tmp_str = " ";
    } else if (isNumber(c)) {
      if (last_char_type != INTEGER && tmp_str != "") {
        partition.push_back(tmp_str);
        tmp_str = "";
      }
      last_char_type = INTEGER;
      tmp_str += c;
    } else if (isOperator(c)) {
      if (tmp_str != "") {
        partition.push_back(tmp_str);
        tmp_str = "";
      }
      last_char_type = OPERATOR;
      tmp_str = string(1,c);
    } else {
      throw runtime_error("Unknown character: " + c);
    }
  }
  if (tmp_str != "") {
    partition.push_back(tmp_str);
  }

  return partition;
};


vector<Token> tokenize(const string &eqn) {
  vector<string> eqn_part = equation_partition(eqn);

  // fix the minus sign for negative integers

  vector<Token> tokens;
  for(int i=0; i<eqn_part.size(); i++) {
    string s = eqn_part[i];
    if (s == "-") {
      if ( (i < eqn_part.size()-1 && isInteger(eqn_part[i+1])) &&  // the next token must be a number
           (tokens.size() == 0 || ( !tokens.back().isConstant() &&  // the previous token cannot be a number or ")"
                                    tokens.back().getOperator() != Token::CLOSE_PARENTHESIS_OPERATOR) ))
      {
        tokens.push_back(Token(s + eqn_part[i+1]));
        i++;    //  skip the next number
      } else {
        tokens.push_back(Token(s));
      }
    } else if (s != " ") {
      tokens.push_back(Token(s));
    } // else s == " "  -> skip
  }

  return tokens;
}

