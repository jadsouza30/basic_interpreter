#include "arithmetic.h"
#include <exception>
#include "map"
using namespace std;

NumericExpression::~NumericExpression(){

}

void NumericExpression::set_maps(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  this->vars=vars;
  this->arrays=arrays;
}

BinaryExpression::BinaryExpression(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  this->vars=vars;
  this->arrays=arrays;
}

//assigns the correct type of Numeric Expression to a pointer
NumericExpression* NumericExpression::helper(std::stringstream& data){
  char top;
  NumericExpression* returnval;

  while(isspace(data.peek())){
    data>>noskipws>>top; //ignore whitespace
  }

  if(data.peek()=='('){//parenthesis means binary exp
    returnval=new BinaryExpression(vars,arrays);
  }

  else if(data.peek()=='-' or isdigit(data.peek())){
    returnval=new Constant; //is an int so constant
  }

  else{
    returnval=new Variable(vars,arrays); //only other option
  }

  returnval->parse(data);
  return returnval;
}


void BinaryExpression::parse(stringstream& data){
  char top;
  data>>skipws>>top;

  if(top!='('){
      cerr<<"no opening parenthesis found"<<endl;
  }

  //parse the first expression
  left=helper(data);

  //read in the operator
  data>>skipws>>operation;

  //parse the second expression;
  right=helper(data);

  data>>skipws>>top;

  //must have a closing parenthesis
  if(top!=')'){
    cerr<<"no closing parenthesis"<<endl;
  }
}

string BinaryExpression::format(){

  //formatting with correct spacing and parenthesis
  string returnval="("+left->format()+" "+operation+" "+right->format()+")";
  return returnval;
}

BinaryExpression::~BinaryExpression() {
    //deallocate assignments from parse function
    delete this->left;
    delete this->right;
}

int BinaryExpression::evaluate(){
  int first=left->evaluate();
  int second=right->evaluate();
  stringstream stream;
  stream<<"zero "<<left->format()<<" "<<left->evaluate()<<" "<<right->format()<<" "<<right->evaluate();
  if(operation=='/'){
    if(second==0){
      throw stream;
    }
    else{
      return first/second;
    }
  }
  if(operation=='*'){
    return first*second;
  }
  if(operation=='+'){
    return first+second;
  }
  if(operation=='-'){
    return first-second;
  }
  else{
    return false;
  }
}

void Constant::parse(stringstream& data){

  //just read in an int from stream
  data>>skipws>>val;
}

string Constant::format(){

  //convert int to string
  stringstream stream;
  stream<<val;
  return stream.str();
}

int Constant::evaluate(){
  return val;
}

Constant::~Constant(){
 //nothing to be done
}

//Variable Functions

Variable::Variable(){

}

Variable::Variable(std::map <std::string,int>* vars, std::map <std::string, std::map<int,int> >* arrays){
  this->vars=vars;
  this->arrays=arrays;
}

void Variable::parse(stringstream& data){
  char top;
  //ignore whitespace
  while(isspace(data.peek())){
    data>>noskipws>>top;
  }

  //read in the name of the var
  while(isupper(data.peek())){
    data>>skipws>>top;
    name+=top;
  }

  is_array=false;

  //ignore whitepsace again
  while(isspace(data.peek())){
    data>>noskipws>>top;
  }

  //is an array type if brackets found
  if(data.peek()=='['){

    data>>top;
    is_array=true;

    //parse the index value
    index=helper(data);

    data>>top;

    if(top!=']'){
      cerr<<"no closing bracket found"<<endl;
    }
  }
}

string Variable::format(){
  if(is_array){
    string temp=name;
    temp+="[";
    temp+=index->format();
    temp+="]";
    return temp;
  }
  return name;
}

Variable::~Variable(){
  //no deallocation needed if not an array
  if(is_array){
    delete this->index;
  }
}

bool Variable::is_arr(){
  return is_array;
}

string Variable::get_name(){
  return name;
}

int Variable::get_index(){
  return index->evaluate();
}

int Variable::evaluate(){
  if(is_array){
    //search map of arrays
    std::map <std::string, std::map<int,int> >::iterator it=arrays->find(name);

    if(it==arrays->end()){ //was not found, retunr 0
      return 0;
    }

    else{
      std::map <int,int>::iterator it2=it->second.find(index->evaluate());

      if(it2==it->second.end()){//was not found reutnr 0
        return 0;
      }

      else{//return stored value
        return it2->second;
      }
    }
  }

  else{
    std::map<string,int>::iterator it=vars->find(name);

    if(it==vars->end()){//not found return 0
      return 0;
    }

    else return it->second; //retunr stored value
  }
}
