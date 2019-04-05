
#include "Ordlistan.h"

worder::worder(std::ifstream & is):word_count{}
{
  
  auto to_map = [this](std::string str)
    {
      auto hej = this->word_count.emplace(str,1); 
      if(!hej.second)
	{
	  ++(hej.first)->second;
	}
     
    };
  
  std::vector<std::string> stinger;
  stinger = readwords(is);

  std::for_each(stinger.begin(), stinger.end(), to_map);
}


void worder::out_data(std::ostream & os)
{
  auto print= [&os] (std::pair<std::string,unsigned int> item)
  {
    os<<item.first<<": "<<item.second<<std::endl;
    
  };

    std::for_each(word_count.begin(),word_count.end(),print);
  
}

std::vector<std::string> worder::readwords(std::ifstream & is)
{
  std::string line;
  std::vector<std::string> strings;

  std::getline(is,line, static_cast<char>EOF);
  std::string tempstring;


  auto isblankk = [](char c){
      return (isblank(c)|| c == '\n');
  };

    auto push_in = [&](std::string &arg)
    {
        arg = line.substr(0, static_cast<unsigned int>(std::find_if(line.begin(), line.end(), isblankk) - line.begin()) );
        line.erase(0, static_cast<unsigned int>(std::find_if( line.begin(), line.end(), isblankk) - line.begin()+1 ) );
        clean(arg);

        if(!islegal(arg))
        {
            arg = "";
        }
    };

  strings.resize(static_cast<unsigned int>(std::count_if(line.begin(),line.end(),[](char i){return isblank(i)||i == '\n';} )));

  std::for_each(strings.begin(),strings.end(),push_in);

    strings.erase(std::remove(strings.begin(),
                              strings.end(),
                              ""),strings.end());
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
          }
          else
          {keep_going = true;}
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

    std::for_each(str.begin(),str.end(), transistor);
    keep_going = false;
    std::reverse(str.begin(),str.end());
    std::for_each(str.begin(),str.end(), transistor2);
    std::reverse(str.begin(),str.end());
  
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
 
