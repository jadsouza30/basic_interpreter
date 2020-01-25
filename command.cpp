#include "command.h"
#include "arithmetic.h"
#include <exception>
#include <sstream>

using namespace std;

Command::~Command(){

}

NumericExpression* Command::helper(stringstream& data){
  char top;
  NumericExpression* returnval;

  while(isspace(data.peek())){ //skip whitespace
    data>>noskipws>>top;
  }

  //if block decides correct sub class
  if(data.peek()=='('){
    returnval=new BinaryExpression(vars,arrays);
  }

  else if(data.peek()=='-' or isdigit(data.peek())){
    returnval=new Constant;
  }

  else{
    returnval=new Variable(vars,arrays);
  }

  returnval->parse(data);
  return returnval;
}

If::If(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  //maps passed from line component to this object
  this->vars=vars;
  this->arrays=arrays;
}

void If::parse(stringstream& data){
  data>>skipws>>key_word; //read in type of command
  bool_val=new BoolExp(vars,arrays); //initialize pointer
  bool_val->parse(data); //fill out data members
  string thn;
  data>>skipws>>thn; //read in "THEN"
  data>>jump; //read in line to jump to
}

string If::format(){
  stringstream jumps;
  jumps<<jump;

  //for pretty printing
  string returnval=key_word+" "+bool_val->format()
  +" "+"THEN "+"<"+jumps.str()+">";
  return returnval;
}

void If::execute(){
  if(bool_val->evaluate()){
    throw jump; //notify interpreter which line to go to
  }
}

If::~If(){
  //deallocate pointer
  delete this->bool_val;
}

Let_Var::Let_Var(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  //maps passed from lien to this obejct
  this->vars=vars;
  this->arrays=arrays;
}

void Let_Var::parse(stringstream& data){
  data>>skipws>>key_word; //read in typ eof command
  var=new Variable(vars,arrays);
  var->parse(data);
  val=helper(data); //parse the value being assigned
}

string Let_Var::format(){//pretty printing
  string returnval=key_word+" "+var->format()+" "+val->format();
  return returnval;
}

void Let_Var::execute(){
  if(var->is_arr()){
    string name=var->get_name();
    //search map of arrays based on just name
    std::map <std::string, std::map<int,int> >::iterator it=arrays->find(name);

    if(it==arrays->end()){//if not found, make and insert a new entry
      std::map<int,int> temp;
      int keyv=var->get_index();
      temp.insert(std::pair<int,int>(keyv,val->evaluate()));
      arrays->insert(pair<string,map<int,int>>(name,temp));
    }

    else{
      std::map <int,int>::iterator it2=it->second.find(var->get_index());

      if(it2==it->second.end()){//if not found, make a new entry
        it->second.insert(std::pair<int,int>(var->get_index(),val->evaluate()));
      }

      else{//otherwise overwrite
        it2->second=val->evaluate();
      }
    }
  }

  else{
    std::map<string,int>::iterator it=vars->find(var->get_name());

    if(it==vars->end()){
      vars->insert (pair<string,int>(var->get_name(),val->evaluate()) );
    }

    else it->second=val->evaluate();
  }
}

Let_Var::~Let_Var(){
  //deallocate pointer
  delete this->var;
  delete this->val;
}


void Goto::parse(stringstream& data){
  key_word="GOTO";
  data>>skipws>>jline; //read in line to jump to
}

string Goto::format(){
  stringstream j;
  j<<jline; //for converitng int to string
  string returnval=key_word+" "+"<"+j.str()+">";
  return returnval;
}

void Goto::execute(){
  stringstream stream;

  stream<<"GOTO"<<" "<<jline;
  throw stream;
}

Goto::~Goto(){
  //nothing to be done
}

Print::Print(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  this->vars=vars;
  this->arrays=arrays;
}

void Print::parse(stringstream& data){
  data>>skipws>>key_word; //skip whitespace;

  val=helper(data); //parse value to be printed
}

string Print::format(){
  string returnval=key_word+" "+val->format();
  return returnval;
}

void Print::execute(){
  cout<<val->evaluate()<<endl;
}

Print::~Print(){
  delete this->val;
}


void Gosub::parse(stringstream& data){
  key_word="GOSUB";
  data>>skipws>>jline; //read in line to jump to
}

string Gosub::format(){
  stringstream j;
  j<<jline;
  string returnval=key_word+" "+"<"+j.str()+">";
  return returnval;
}

void Gosub::execute(){
  stringstream stream;
  stream<<"GOSUB"<<" "<<jline;
  throw stream;//notify interpreter which line to go to
}

Gosub::~Gosub(){

}

void Ret::parse(stringstream& data){
  data>>skipws>>key_word; //read in command word
}

string Ret::format(){
  return key_word;
}

Ret::~Ret(){

}

void Ret::execute(){
  throw -1; //notify interpreter to RETURN
}

void Ender::parse(stringstream& data){
  data>>skipws>>key_word; //read in type of command
}

string Ender::format(){
  return key_word;
}

void Ender::execute(){
  throw -2; //notify interpreter to terminate
}

Ender::~Ender(){

}
