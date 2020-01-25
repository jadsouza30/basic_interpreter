#include "interpreter.h"

using namespace std;

Interpreter::Interpreter(std::istream& in) {
    this->parse(in);
}

Interpreter::~Interpreter() {
  for(unsigned int i=0;i<program.size();i++){
    delete program[i]; //deallocate memeory for each line
  }
}

void Interpreter::parse(std::istream& in) {
    string lin="";
    Line* linen;

    //parse input line by line
    while (getline(in, lin)) {
        if(lin.size()==0)break; //empty program
        stringstream stream;
        stream<<lin;
        linen=new Line(&vars,&arrays);
        linen->parse(stream);
        program.push_back(linen);
    }
}

void Interpreter::execute(){
  size_t it=0;

  bool cont=true;
  while(it!=program.size()){
    cont=true;

    try{
      program[it]->execute();
    }

    catch(int& sig){

      if(sig==-1){ //RETURN command
        if(subs_indices.empty()){ //check for amtching gosub
          cout<<"Error in Line "<<program[it]->get_line_num()<<
          ": No matching GOSUB for RETURN."<<endl;
          break;
        }
        it=subs_indices.top();
        subs_indices.pop();
        cont=false; //execute exactly starting here
      }
      else if(sig==-2){ //END Command
        break;
      }
      else{ //IF jump to a positive line number
        size_t temp=bin_search(sig);

        if(temp==program.size()){//line not found with binary search
          cout<<"Error in line "<<program[it]->get_line_num()<<": "
          <<"IF jump to non-existent line "<<sig<<'.'<<endl;
          return;
        }

        it=temp;
        cont=false;
      }
    }

    catch(stringstream& stream){
      string comm;
      stream>>comm;

      if(comm=="zero"){//division by zero
        string a1;
        int ae1;
        string a2;
        int ae2;
        stream>>a1>>ae1>>a2>>ae2;
        cout<<"Error in line "<<program[it]->get_line_num()<<": Division by 0: "
        <<a1<<" = "<<ae1<<", "<<a2<<" = "<<ae2<<"."<<endl;
        return;
      }

      if(comm=="GOSUB"){
          subs_indices.push(it+1);
      }

      int jline;
      stream>>jline;
      size_t temp=bin_search(jline);

      if(temp==program.size()){
        cout<<"Error in line "<<program[it]->get_line_num()<<": "<<comm
        <<" to non-existent line "<<jline<<'.'<<endl;
        break;
      }

      it=temp;
      cont=false;
    }

    catch(exception& e){
      cout<<e.what()<<endl;
      break;
    }

    if(cont){
      it++;
    }
  }

}

int Interpreter::bin_search_helper(int line_num, int start, int end){
  //recursive binary search
  if(start>end)return program.size();
  int mid=(end+start)/2;
  int mid_num=program[mid]->get_line_num();
  if(mid_num==line_num)return mid;
  else if(mid_num>line_num)return bin_search_helper(line_num,start,mid-1);
  else return bin_search_helper(line_num,mid+1,end);
}

int Interpreter::bin_search(int line_num){
  //actual function called
  int start=0;
  int end=program.size()-1;
  return bin_search_helper(line_num, start, end);
}

void Interpreter::write(std::ostream& out) {
    //pretty print to a stream
    for(unsigned int i=0;i<program.size();i++){
      out<<program[i]->format()<<endl;
    }
}
