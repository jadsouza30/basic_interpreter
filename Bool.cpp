#include "Bool.h"
#include "arithmetic.h"

using namespace std;

BoolExp::BoolExp(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  this->vars=vars;
  this->arrays=arrays;
}

NumericExpression* BoolExp::helper(std::stringstream& data){
  char top;
  NumericExpression* returnval;

  while(isspace(data.peek())){ //skip whitespace
    data>>noskipws>>top;
  }

  //if block decides correct type to assign
  if(data.peek()=='('){
    returnval=new BinaryExpression(vars, arrays);
  }

  else if(data.peek()=='-' or isdigit(data.peek())){
    returnval=new Constant;
  }

  else{
    returnval=new Variable(vars, arrays);
  }

  returnval->parse(data);
  return returnval;
}

void BoolExp::parse(stringstream& data){

  left=helper(data); //parse the first operand

  data>>skipws>>operation; //read in the type of comparison

  right=helper(data); //parse the second operand

}

string BoolExp::format(){
  string returnval="";
  if(operation!='>'){
    returnval="["+left->format()+" "+operation+" "+right->format()
    +"]";
  }
  else{ //switch order of operand and comparison as specified in assignment
    returnval="["+right->format()+" "+"<"+" "+left->format()
    +"]";
  }
  return returnval;
}

BoolExp::~BoolExp(){ //deallocate operands
  delete this->left;
  delete this->right;
}

bool BoolExp::evaluate(){
  int first=left->evaluate();
  int second=right->evaluate();
  //return value based on operation character
  if(operation=='<'){
    return first<second;
  }

  else if(operation=='>'){
    return first>second;
  }

  else{
    return first==second;
  }
}
