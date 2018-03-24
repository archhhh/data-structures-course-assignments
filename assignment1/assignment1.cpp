//
// assignment1.cpp (Version 1.0)
//
// Please write your name, your student ID, and your email address here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
/*
  Artyom Chen 20162017 artychen13@unist.ac.kr
  Function getPriority uses switch operator to check the type of the operator.
  Returns the corresponding values representing the incoming priority of the operator.
  The less the value, the higher the priority. If no type corresponds, throws an exception.
  Function getInStackPriority has the same implementation as getPriority, but returns instack priority values.
  Function postfix converts already tokenized infix expression to postfix expression.
  Vector result contains the postfix expression and stack is used to contain operators. If the operand is
  encountered, simply add it to the resultant vector that represents the postfix expression. If
  the operator follows, add all the operators with higher priority from the stack to the vector and
  add the following operator to the stack. If the operator is closing bracket, add all the operators from the stack
  until the opening bracket is met. After all the operations, add all the remaining operators that are left in the stack to the vector.
  This function throws the following exceptions. If there is opening bracket and the closing bracket is
  missing, it throws an exception. If there is closing bracket and the opening bracket is missing,
  it throws an exception.
  Function eval evaluates postfix expression. The function is implemented with the help of stack.
  It traverses through the expression, if the operator is encountered, adds it to the stack, otherwise, takes two operators from the stack and make
  the corresponding evaluation. The resultant value is put back to the stack. By the end of the iteration
  the resultant value is value in the stack. Function throws exceptions, if there are no operators left
  to use the operand on, or when there are no operands left to perform the expression on the operands.
*/
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
