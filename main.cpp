#include "line.h"
#include "Bool.h"
#include "command.h"
#include "interpreter.h"
#include "arithmetic.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
  if(argc<2){ //check if file name was specified
    cerr<<"Please enter an input file."<<endl;
    return 1;
  }

  ifstream in(argv[1]);

  if(in.fail()){ //check if file can be opened
    cout<<"File "<<argv[1]<<" cannot be opened."<<endl;
    return 1;
  }

  Interpreter inter(in); //parses the file
  inter.execute(); //executes the program
}
