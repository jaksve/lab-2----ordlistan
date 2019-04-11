#ifndef Ordlistan_h
#define Ordlistan_h
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <iterator>
#include <stdexcept>
#include <iomanip>
enum flag_type {a,f,o};

class worder
{
public:
    worder(std::ifstream & is):words{readwords(is)}{}
    void out_data(std::ostream & os,char print_type, int cnt = 0);

private:
    std::vector<std::string> readwords(std::ifstream & is);
    std::vector<std::string> words;
};

#endif

