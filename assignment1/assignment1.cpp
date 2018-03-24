// Artyom Chen 20162017 artychen13@unist.ac.kr
//
// assignment1.cpp (Version 1.0)
//
// Please write your name, your student ID, and your email address here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//


// include header filers here
#include "assignment1.h"
#include <stdexcept>
#include "LinkedStack.h"
#include <vector>
using namespace std;

int getPriority(Token token) {
    switch(token.getOperator())
    {
      case 0: return 3;
              break;
      case 1: return 3;
              break;
      case 2: return 2;
              break;
      case 3: return 2;
              break;
      case 4: return 0;
              break;
      default:
              throw runtime_error("Wrong operator");
    }
}

int getInStackPriority(Token token) {
    switch(token.getOperator())
    {
      case 0: return 3;
              break;
      case 1: return 3;
              break;
      case 2: return 2;
              break;
      case 3: return 2;
              break;
      case 4: return 8;
              break;
      default:
              throw runtime_error("Wrong operator");
    }
}
vector<Token> postfix(const vector<Token>& expression) {
    vector <Token> result;
    LinkedStack<Token> stack;
    for(int i = 0; i < expression.size(); i++)
    {
        if(expression[i].isConstant())
        {
          result.push_back(expression[i]);
        }else if(expression[i].getOperator() == 5)
        {
          for(;stack.top().getOperator() != 4; stack.pop())
          {
            result.push_back(stack.top());
          }
          stack.pop();
        }else
        {
          while(!stack.empty() && (getInStackPriority(stack.top()) <= getPriority(expression[i])))
          {
            result.push_back(stack.top());
            stack.pop();
          }
          stack.push(expression[i]);
        }
    }
    while(!stack.empty())
    {
      if(stack.top().getOperator() == 4)
        throw runtime_error("Missing close parethnesis in an infix expression.");
      result.push_back(stack.top());
      stack.pop();
    }
    return result;
}
int eval(const vector<Token>& expression) {
    LinkedStack <Token> stack;
    for(int i = 0; i < expression.size(); i++)
    {
      if(expression[i].isConstant())
      {
        stack.push(expression[i]);
      }else{
        if(stack.empty())
          throw runtime_error("Cannot apply an operator on empty stack");
        if(stack.size() == 1)
          throw runtime_error("Cannot apply an operator to a stack with one integer only");
        Token a = stack.top();
        stack.pop();
        Token b = stack.top();
        stack.pop();
        Token*c;
        switch(expression[i].getOperator())
        {
          case 0:c = new Token(b.getConstant()+a.getConstant());
                 break;
          case 1:c = new Token(b.getConstant()-a.getConstant());
                 break;
          case 2:c = new Token(b.getConstant()*a.getConstant());
                 break;
          case 3:c = new Token(b.getConstant()/a.getConstant());
                 break;
          default:
                 runtime_error("Wrong operator");
        }
        stack.push(*c);
        delete c;
      }
    }
    if(stack.size() == 1)
      return stack.top().getConstant();
    else
      throw runtime_error("Unfinished evaluation due to missing operators.");
}
