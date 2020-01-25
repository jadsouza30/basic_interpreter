#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Bool.h"
#include "arithmetic.h"
#include <map>

class Command {
public:
  //assings correct sub class for NumExp pointer
  NumericExpression* helper(std::stringstream&);
  virtual void parse(std::stringstream&)=0; //create the parse tree
  virtual std::string format() = 0; //for printing
  virtual ~Command()=0;
  virtual void execute()=0;
protected:
  std::string key_word=""; //type of command
  std::map <std::string,int>* vars;
  std::map <std::string, std::map<int,int> >* arrays;
};

class If:public Command{
public:
  If(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays);
  void parse(std::stringstream&);
  std::string format();
  ~If();
   void execute();
private:
  BoolExp* bool_val;
  int jump; //line to go to if true
};

class Let_Var:public Command{
public:
  Let_Var(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays);
  void parse(std::stringstream&);
  std::string format();
  ~Let_Var();
   void execute();
private:
  Variable* var; //variable being assigned a value
  NumericExpression* val; //the value being assigned

};

class Print:public Command{
public:
  Print(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays);
  void parse(std::stringstream&);
  std::string format();
  ~Print();
  void execute();
private:
  NumericExpression* val; //value being outputted
};

class Goto:public Command{
public:
  void parse(std::stringstream&);
  std::string format();
  ~Goto();
   void execute();
private:
  int jline; //line to go to
};

class Gosub:public Command{
public:
  void parse(std::stringstream&);
  std::string format();
  ~Gosub();
  void execute();
private:
  int jline; //line to go to

};

class Ret:public Command{
public:
  void parse(std::stringstream&);
  std::string format();
  ~Ret();
  void execute();
};

class Ender:public Command{
public:
  ~Ender();
  void parse(std::stringstream&);
  std::string format();
  void execute();
};

#endif
