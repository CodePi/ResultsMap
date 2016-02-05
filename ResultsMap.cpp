// From the personal library of Paul Ilardi (http://github.com/CodePi).
// Free to use or modify.

#include "ResultsMap.h"
#include <vector>

using namespace std;

namespace codepi {

ResultsMap& ResultsMap::operator()(const string& key){
  AnyType*ap = &valMap[key];
  ResultsMap*rmp = anyType_cast<ResultsMap>(ap);
  if(rmp) return *rmp;  // if it exists, return it
  else{                 // otherwise create one
    *ap = ResultsMap();
    rmp = anyType_cast<ResultsMap>(ap);
  }
  return *rmp;
}

AnyType& ResultsMap::operator[](const string& key){
  return valMap[key];
}

int ResultsMap::count(const std::string& key) {
  return valMap.count(key) && !valMap[key].empty();
}

int ResultsMap::size() const{
  int size=0;
  // valMap may contain empty entries, don't count those
  for(ValMap::const_iterator i=valMap.begin();i!=valMap.end();i++){
    if(!i->second.empty()) size++;
  }
  return size;
}

string ResultsMap::toString(int numIndent, bool compact){
  stringstream ss;
  toStream(ss,numIndent,compact);
  return ss.str();
}

ostream& operator<<(std::ostream& s, ResultsMap& rm){
  rm.toStream(s,0);
  return s;
}

ostream& ResultsMap::toStream(ostream& ss,int numIndent,bool compact){
  for(ValMap::iterator i=valMap.begin();i!=valMap.end();i++){
    if(i->second.empty()) continue; //don't print if empty

    if(!compact) for(int j=0;j<numIndent;j++) ss<<"  ";
    if(compact&&i!=valMap.begin()) ss<<";";

    ResultsMap* p = anyType_cast<ResultsMap>(&i->second); //check if resultsMap
    if(p && p->isEmpty()) continue; //don't print empty resultsMap
    ss<<i->first<<"=";
    if(p){ //resultsMap
      if(compact) ss<<"{";
      else ss<<endl;
      p->toStream(ss,numIndent+1,compact);
      if(compact) ss<<"}";
    }else{
      ss<<i->second;
      if(!compact) ss<<endl;
    }
  }

  return ss;
}

void ResultsMap::merge(const ResultsMap& other){
  for(ValMap::const_iterator i=other.valMap.begin();i!=other.valMap.end();i++){
    valMap[i->first]=i->second;
  }
}

} // end namespace codepi
