
#include "Ordlistan.h"

worder::worder(std::ifstream & is,std::string arg, int count):word_count{}
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

    std::vector<std::string> strings{(static_cast<unsigned int>(std::count_if(line.begin(),line.end(),[](char i){return isblank(i)||i == '\n';} ))) };

  std::for_each(strings.begin(),strings.end(),push_in);

    strings.erase(std::remove(strings.begin(),
                              strings.end(),
                              ""),strings.end());
  return strings;
}
  
void worder::clean(std::string & str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    str.erase(0,str.find_first_not_of("\"\'()") );
    std::reverse(str.begin(),str.end());

    str.erase(0,str.find_first_not_of(" ?!;:,.\"\')") );
    std::reverse(str.begin(),str.end());

    if(str[str.size() - 2] == '\'' && str.back() == 's')
    {
        str.erase(str.size() - 2);
    }
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


