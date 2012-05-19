// From the personal library of Paul Ilardi (code@pilardi.com).
// Free to use or modify.

#pragma once

#include<map>
#include<string>
#include<sstream>
#include<memory>
#include"AnyType.h"

class ResultsMap{
public:
	ResultsMap& operator()(const std::string& key);
   boost_mod::AnyType& operator[](const std::string& key);
	std::string toString(int numIndent=0,bool compact=false);
	std::ostream& toStream(std::ostream& stream,int numIndent=0,bool compact=false);
   int size() const;
   void clear() {valMap.clear();}
   bool isEmpty() const {return size()==0;}
   int count(const std::string& key);
   void merge(const ResultsMap& other); //merges the contents of other into this
   void erase(const std::string& key) {valMap.erase(key);}
   typedef std::map<std::string, boost_mod::AnyType>::iterator iterator;
   iterator begin() {return valMap.begin();}
   iterator end() {return valMap.end();}
private:
	typedef std::map<std::string, boost_mod::AnyType> ValMap;
	ValMap valMap;
};

std::ostream& operator<<(std::ostream& s, ResultsMap& rm);
