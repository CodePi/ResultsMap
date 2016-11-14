#include <iostream>
#include "../ResultsMap.h"
#include<vector>
#include<list>
#include<set>
#include<queue>
#include<deque>

using namespace std;
using namespace codepi;

int main(){
  ResultsMap rm;
  AnyType x=4;
  rm["a"]=1;
  rm["f"]=x;
  rm("b")["c"]=5;
  rm("b")("d")["e"]="hello";
  
  ResultsMap rm2;
  rm2["x"]=1.5;
  rm2["y"]=4.5;
  
  rm("z")=rm2;
  rm["q"]=5;
  rm2["x"]=3;
  rm["w"]=rm2;
  
  int arr[]={1,2,3,4,5};
  rm("c")["b"]=vector<int>(arr,arr+5);
  rm("c")["c"]=list<int>(arr,arr+5);
  rm("c")["d"]=set<int>(arr,arr+5);
  rm("c")["f"]=deque<int>(arr,arr+5);
  
  rm["x"];
  int cx=rm.count("x");
  int cc=rm.count("c");
  int cw=rm.count("w");
  
  cout<<rm;
  rm.toStream(cout,0,true);
  cout<<endl;
  cout<<rm["q"]<<endl;
  
  int& i=rm["q"].getRef<int>();
  
  cout<<rm["q"].to_s()<<endl;
  cout<<rm["q"].to_i()<<endl;
  cout<<rm["q"].to_f()<<endl;
  
  try{
    // bad cast
    float& i=rm["q"].getRef<float>();
  }catch(bad_anyType_cast&e){
    cout<<"Testing exceptions: bad_anyType_cast caught\n";
  }

  #ifdef WIN32
  getchar();
  #endif
}
