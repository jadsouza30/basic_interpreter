#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <map>

class NumericExpression{
public:
  //decides which derived class a pointer should be
  NumericExpression* helper(std::stringstream&);
  virtual ~NumericExpression()=0; //deallocator
  virtual void parse(std::stringstream&) =0; //generates parse tree
  virtual std::string format()= 0;//returns pretty printed version
  virtual int evaluate()=0;
  void set_maps(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays);
protected:
  std::map <std::string,int>* vars;
  std::map <std::string, std::map<int,int> >* arrays;
};

class BinaryExpression :public NumericExpression {
public:
  BinaryExpression(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays);
  void parse(std::stringstream&);
  ~BinaryExpression();
  virtual std::string format();
  int evaluate();
private:
  char operation; // can be +,-,*,/
  NumericExpression* left; //first operand
  NumericExpression* right; //second operand
};

class Constant: public NumericExpression{
public:
  void parse(std::stringstream&);
  ~Constant();
  std::string format();
  int evaluate();
private:
  int val; //basically all this type is
};

class Variable: public NumericExpression{

public:
  Variable();
  Variable(std::map <std::string,int>* vars,
    std::map <std::string, std::map<int,int> >* arrays);
  void parse(std::stringstream&);
  ~Variable();
  std::string format();
  int evaluate();
  bool is_arr(); //retunr true if array variable
  std::string get_name(); //return the name, without brackets and index if array
  int get_index(); //return the integer value of the index expression
private:
  std::string name;
  NumericExpression* index;  //the value used by []
  bool is_array; //if it is an array element or normal variable
};

#endif
