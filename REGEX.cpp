#include <regex>
#include <iostream>
#include <iomanip>
#include <vector>
#include<iterator>


std::vector<std::string> Search(const std::regex& pattern, const std::string& sample)
{
    std::vector<std::string>search_result;

    auto begin = std::sregex_iterator(std::begin(sample), std::end(sample), pattern);
    auto end = std::sregex_iterator();
    std::transform(begin, end, std::back_inserter(search_result), [](auto x){return x.str();});

    return search_result;
}


int main()
{
    std::string initial_text;
    std::getline(std::cin,initial_text);

    //HH:MM:SS or H:MM:SS or HH:M:SS or so on
    std::cout<<"Time: \n";
    std::regex time_pattern (R"((\s|^)([01]?[0-9]|[2][0-3]):[0-5]?[0-9]:[0-9]?[0-9](\s|$))");
    for(auto res: Search(time_pattern,initial_text))
        std::cout<<std::setw(8)<<std::setfill(' ')<<res<<"\n";

    //MM.DD.YYYY or M.DD.YYYY or MM.D.YYYY or M.D.YYYY or all this with two YY
    std::cout<<"Date: \n";
    std::regex date_pattern (R"((\s|^)(([0]?[1-9])|([1][0-2]))\.([0-2]?[1-9]|[12][0]|[3][01])\.([0-9]{2})?[0-9]{2}(\s|$))");
    for(auto res: Search(date_pattern,initial_text))
        std::cout<<std::setw(10)<<std::setfill(' ')<<res<<"\n";
    return 0;
}

