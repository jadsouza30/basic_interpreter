#ifndef LINE_HPP
#define LINE_HPP

#include <string>
#include <iostream>
#include "command.h"
#include <map>

class Line{
public:
  Line(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> > *arrays);
  void parse(std::stringstream&); //create parse tree
  Command* helper(std::stringstream&); //assigns correct command type
  std::string format( ); //for printing
  ~Line(); //deallocate memory
  void execute();
  int get_line_num(); //return the line number
private:
  Command* comm; //the actual command
  int line_num; //the current line number
  std::map <std::string,int>* vars; //map for normal variables
  std::map <std::string, std::map<int,int> >* arrays; //map for arrays
};

#endif
