#include "public.hpp"

int main(int argc, char *argv[])
{
    std::vector<int> rand = Public::random_ints(10);
    std::vector<std::string> content;
    for (auto it : rand)
    {
        content.emplace_back(std::to_string(it));
    }
    Public::writeline(content, "./rand.txt");
    std::string src = "1@2@fdakh";
    content = Public::split_delim(src, "@");
    for (auto line : content)
    {
        std::cout << line << std::endl;
    }
    std::cout << "press enter to exit";
    std::cin.get();
    return 0;
}