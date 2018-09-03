//
// main.cpp - Version 1.0
//
// This file is created by Tsz-Chiu Au on 9/24/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include "Token.h"
#include "tokenizer.h"
#include "assignment1.h"

using namespace std;

void printMenu() {
  cout << "Please select one of the following option:" << endl;
  cout << " a) Enter a new expression in infix notation." << endl;
  cout << " b) Print the expression in infix notation." << endl;
  cout << " c) Print the expression in postfix notation." << endl;
  cout << " d) Evaluate the expression." << endl;
  cout << " z) Quit this program." << endl;
}

int main(int argc, char *argv[]) {

  bool isVerbose = true;

  // the -q option turns off some outputs to help grading

  if (argc==2) {
    if (strcmp(argv[1], "-q")==0) {
      isVerbose = false;
    }
  }

  try {

    string expression;

    bool isExit = false;

    while (!isExit) {  // loop until the user choose to quit

      if (isVerbose) printMenu();

      if (isVerbose) cout << "Your choice: ";
      char choice;
      cin >> choice;

      cin.get();  // get rid of the newline character

      if (isVerbose) cout << endl;

      switch (choice) {
        case 'a':  // enter the expression in infix notation
          if (isVerbose) cout << "Please enter an expression in infix notation: ";
          getline(cin, expression);
          break;
        case 'b': {  // tokenize the expression and print it.
          vector<Token> token = tokenize(expression);
          for (vector<Token>::const_iterator iter = token.begin(); iter != token.end(); iter++) {
            cout << *iter << " ";
          }
          cout << endl;
          break;
        }
        case 'c': {  // convert the expression into postfix notation and print it
          vector<Token> ps = postfix(tokenize(expression));
          for (vector<Token>::const_iterator iter = ps.begin(); iter != ps.end(); iter++) {
            cout << *iter << " ";
          }
          cout << endl;
          break;
        }
        case 'd': {  // evaluate the expression
          int x = eval(postfix(tokenize(expression)));
          if (isVerbose) cout << "The result is ";
          cout << x << endl;
          break;
        }
        case 'z':  // exit the program
          if (isVerbose) cout << "Bye!" << endl;
          isExit = true;
          break;
        default:
          cout << "Error: Unknown option." << endl;
      }
      if (isVerbose) cout << endl;
    }

    return 0;

  } catch(const exception& e) {
    // The error message should be printed to cerr,
    // but for grading purpose, we print it to cout.
    cout << "Error: " << e.what() << endl;
  }
}
