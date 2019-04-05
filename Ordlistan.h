#ifndef Ordlistan_h
#define Ordlistan_h
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <list>
#include <map>
class worder
{
 public:
  worder(std::ifstream & is);
  void out_data(std::ostream & os);

 private:
std::vector<std::string> readwords(std::ifstream & is);
void clean(std::string & str);
bool islegal(std::string str);
 std::map<std::string , unsigned int> word_count; 
};
#endif
