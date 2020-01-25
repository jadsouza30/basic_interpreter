#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <fstream>
#include "line.h"
#include <vector>
#include <map>
#include <stack>

class Interpreter {
public:
  Interpreter(std::istream&);
  void execute(); //execute the program
  void parse(std::istream& in); //parse
  ~Interpreter(); //deallocate memory
  void write(std::ostream&); //not used in this assignment
private:
  std::ifstream source; //the input file
  std::vector<Line*> program; //stores the lines
  std::stack <int> subs_indices; //stores GOSUBS for return commands
  std::map <std::string, int> vars; //normal vars
  std::map <std::string, std::map<int,int> > arrays; //arrays
  int bin_search_helper(int line_num, int start, int end);
  int bin_search(int line_num); //figure out which line ojbect to execute next
};

#endif
