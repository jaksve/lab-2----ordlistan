
#include "Ordlistan.h"

worder::worder(std::ifstream & is):words{readwords(is)},word_count{}
{}

void worder::out_data(std::ostream & os,char print_type,int cnt =0)
{
    int n = 0;
  auto print= [&os] (std::pair<std::string,unsigned int> item)
  {
    os<<item.first<<": "<<item.second<<std::endl;
    
  };
  auto compare = [](std::pair<std::string,unsigned int> const& lhs, std::pair<std::string,unsigned int> const& rhs)
          {
        return lhs.second > rhs.second;
          };
  auto printlad = [&n,cnt,&os](std::string str)
  {
      n+=str.size();
      if(n > cnt){
          n=str.size()+1;
          os<<'\n';
      }
      os<<str<<' ';
  };
  std::map<std::string,unsigned int> map_words;
    auto to_map = [&map_words](std::string str)
    {
        auto hej = map_words.emplace(str,1);
        if(!hej.second)
        {
            ++(hej.first)->second;
        }
    };

    std::for_each(words.begin(),words.end(),to_map);
    std::vector<std::pair<std::string, unsigned int>> setofwords {map_words.begin(),map_words.end()};
    switch (print_type)
    {
        case 'a':
        std::for_each(setofwords.begin(), setofwords.end(), print);
        break;
        case 'f':
            std::sort(setofwords.begin(),setofwords.end(),compare);
            std::for_each(setofwords.begin(),setofwords.end(),print);
            break;
        case 'o':
            std::for_each(words.begin(), words.end(), printlad);
            break;
        default:
            //fixa throw error{"Missing second argument"};
            break;
    }
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

    if(!str.empty())
    {
        str.erase(str.find_last_not_of(" ?!;:,.\"\')")+1);
    }

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


