#include <string>
#include <sstream>
#include <iostream>
#include "line.h"
#include "command.h"

using namespace std;

Line::Line(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  //pass maps to the line object
  this->vars=vars;
  this->arrays=arrays;
}

Command* Line::helper(stringstream& data){
  char top;
  Command* returnval=NULL;

  //skip whitespace
  while(isspace(data.peek()))data>>noskipws>>top;

  //if block decides type of command to assign
  if(data.peek()=='I'){
    returnval=new If(vars,arrays);
    returnval->parse(data);
    return returnval;
  }

  else if(data.peek()=='P'){
    returnval=new Print(vars,arrays);
    returnval->parse(data);
    return returnval;
  }

  else if(data.peek()=='L'){
    returnval=new Let_Var(vars,arrays);
    returnval->parse(data);
    return returnval;
  }

  else if(data.peek()=='R'){
    Command* returnval=new Ret;
    returnval->parse(data);
    return returnval;
  }
  else if(data.peek()=='E'){
    Command* returnval=new Ender;
    returnval->parse(data);
    return returnval;
  }

  else if(data.peek()=='G'){
    string comm;
    data>>skipws>>comm;

    if(comm[2]=='T'){ //is a GOTO
      returnval=new Goto;
      returnval->parse(data);
      return returnval;
    }

    else{ //is a GOSUB
      returnval=new Gosub;
      returnval->parse(data);
      return returnval;
    }
  }

  return returnval;
}

void Line::parse(stringstream& data){
  data>>skipws>>line_num; //read in line number
  comm=helper(data); //parse command
}

string Line::format(){
  stringstream stream;
  stream<<line_num;

  //add spacing
  string returnval=stream.str()+" "+comm->format();
  return returnval;
}

int Line::get_line_num(){
  return line_num;
}

void Line::execute(){
  //simply execute the command object
  comm->execute();
}

Line::~Line(){
  //deallocate dynamic memory
  delete this->comm;
}
