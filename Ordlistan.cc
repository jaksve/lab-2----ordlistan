#include "Ordlistan.h"

void worder::out_data(std::ostream & os,char print_type , int cnt)
{
    int n{};
    int wrd_length{};
    int int_length{};


    auto longest_word=[&wrd_length,&int_length](std::pair<std::string,unsigned int> &item){
        if(item.first.length()>wrd_length){wrd_length = item.first.length();}

        if(std::to_string(item.second).length()>int_length)
        {
            int_length = std::to_string(item.second).length();
        }
    };

    auto print= [&os,&wrd_length,&int_length,&print_type] (std::pair<std::string,unsigned int> item)
    {
        std::ostream_iterator<std::string> os_i {os," "};
        std::ostream_iterator<unsigned int> os_int{os, "\n"};

        os.setf(std::ios_base::left);
        if(print_type == 'f')
        {
            os.setf(std::ios_base::right);
        }
        os.width(wrd_length);

        os_i = item.first;
        os.setf(std::ios_base::right);
        os.width(int_length);
        os_int = item.second;
        os.unsetf(std::ios_base::right);
        os.unsetf(std::ios_base::left);

        //os<<std::setw(n)<<item.first<<": "<<item.second<<std::endl;
    };
    auto compare = [](std::pair<std::string,unsigned int> const& lhs, std::pair<std::string,unsigned int> const& rhs)
    {
        return lhs.second > rhs.second;
    };

    auto printlad = [&n,cnt,&os](std::string str)
    {
        std::ostream_iterator <std::string> os_i{os," "};
        n+=str.size();
        if(n > cnt){
            n=str.size()+1;
            str+='\n';
            //os<<'\n';
        }
        os_i = str;
    };

    std::map<std::string,unsigned int> map_words;

    std::for_each(words.begin(),words.end(),[&map_words](std::string s){map_words[s]++;});
    std::vector<std::pair<std::string, unsigned int>> setofwords {map_words.begin(),map_words.end()};
    std::for_each(setofwords.begin(),setofwords.end(), longest_word);

    switch (print_type)
    {
        case 'a':
            std::for_each(setofwords.begin(), setofwords.end(), print);
            break;
        case 'f':
            for_each(words.begin(),words.end(),[&n](std::string s){if(static_cast<int>(s.size())>n){n = static_cast<int>(s.size());}});
            std::sort(setofwords.begin(),setofwords.end(),compare);
            std::for_each(setofwords.begin(),setofwords.end(),print);
            break;
        case 'o':
            std::for_each(words.begin(), words.end(), printlad);
            break;
        default:
            throw std::logic_error{"Wrong second argument"};
            break;
    }
}

std::vector<std::string> worder::readwords(std::ifstream & is)
{
    auto cleanse = [](std::string str)
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
        return str;
    };

    auto legalize = [](std::string str)
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
    };
    std::vector<std::string> strings;
    std::vector<std::string> strings2;
    copy(std::istream_iterator<std::string>(is),std::istream_iterator<std::string>(),inserter(strings,strings.begin()));
    transform(strings.begin(),strings.end(),strings.begin(),cleanse);
    copy_if(strings.begin(),strings.end(),inserter(strings2,strings2.begin()),legalize);
    return strings2;
}