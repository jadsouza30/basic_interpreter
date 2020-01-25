#ifndef Bool_HPP
#define Bool_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "arithmetic.h"
#include <map>

class BoolExp{
public:
  //decides derived class types for the two operands
  BoolExp(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays);
  NumericExpression* helper(std::stringstream&);
  void parse(std::stringstream&); //creates the parse tree
  std::string format(); //returns pretty printed version
  ~BoolExp();
  bool evaluate();

private:
  NumericExpression* left; //first operand
  NumericExpression* right; //second operand
  char operation; //type of comparison
  std::map <std::string,int>* vars;
  std::map <std::string, std::map<int,int> >* arrays;
};

#endif
