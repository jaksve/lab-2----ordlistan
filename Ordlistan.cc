
#include "Ordlistan.h"
#include <set>
#include<functional>
worder::worder(std::ifstream & is, std::string arg):allwords{}, word_count{}
{
  
  auto to_map = [this](std::string str)
    {
      auto hej = this->word_count.emplace(str,1); 
      if(!hej.second)
	{
	  ++(hej.first)->second;
	}
     
    };
  
  allwords = readwords(is);
  std::for_each(allwords.begin(), allwords.end(), to_map);
}


void worder::out_data(std::ostream & os)
{
  
  auto compare = [](std::pair<std::string,unsigned int> const& lhs, std::pair<std::string,unsigned int> const& rhs)
    {
      return lhs.second > rhs.second;
    };
  
  std::vector<std::pair<std::string, unsigned int> > setofwords {word_count.begin(),word_count.end()};
   
  std::sort(setofwords.begin(),setofwords.end(),compare);
  
  auto print= [&os] (std::pair<std::string,unsigned int> item)
  {
    os<<item.first<<": "<<item.second<<std::endl;
    
  };
	      
  std::for_each(setofwords.begin(),setofwords.end(),print);
  
}

std::vector<std::string> worder::readwords(std::ifstream & is)
{
  std::string line;
  std::vector<std::string> strings;
  while(is >> line)
    {
      clean(line);
      if(islegal(line))
	{
	  strings.push_back(line);
	  //std::cout << line << std::endl;
	}
    }
  return strings;
}
  
void worder::clean(std::string & str)

{
  std::list<char>const forbidden_start{'\"', '\'', '('};
  std::list<char>const forbidden_end{'?', '!', ';', ':', ',',
      '.', '\"', '\'', ')'};
  bool keep_going{false};
  auto transistor = [&keep_going,forbidden_start,&str](char c)
  {
      if(!keep_going)
      {
          if(forbidden_start.end() != std::find(forbidden_start.begin(), forbidden_start.end(), c))
          {
              str.erase(str.begin());
	      std::cout<<"illegal character in beginning: "<<c<<'\n'; 

          }
          else
          {
	    std::cout<<"legal character in beginning: "<<c<<'\n'; 

	    keep_going = true;}
      }
  };
  
    auto transistor2 = [&keep_going,forbidden_end,&str](char c)
    {
        if(!keep_going)
        {
            if(forbidden_end.end() != std::find(forbidden_end.begin(), forbidden_end.end(), c))
            {
                str.erase(str.begin());
            }
            else
            {keep_going = true;}
        }
    };
    //std::string::iterator it = str.begin();
    std::cout<<"före: "<<str<<std::endl;
    std::for_each(str.begin(),str.end(), transistor);
    std::cout<<"efter: "<<str<<std::endl;
    /*
    std::for_each(str.begin(),str.end(), transistor);
    keep_going = false;
    std::reverse(str.begin(),str.end());
    std::for_each(str.begin(),str.end(), transistor2);
    std::reverse(str.begin(),str.end());
    */
    if(str[str.size() - 2] == '\'' && str.back() == 's')
      {
	str.erase(str.size() - 2);
      }
  
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool worder::islegal(std::string str)
{
  bool validator{str.length() > 2 && str.back() != '-' && str.front() != '-' &&str.find("--") == std::string::npos};
  
  auto lol = [&validator](char c)
    {
      if(!isalpha(c) && c != '-')
	{
	  validator = false;
	}
    };  
  std::for_each(str.begin(), str.end(), lol);
    return validator;
}
 
