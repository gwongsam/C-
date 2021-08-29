// #include <iostream>
// #include <filesystem>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <random>
// #include <regex>

// class Public
// {
// public:
//     static int random_int(size_t sub = 0, size_t upper = 100)
//     {
//         static std::random_device rd;
//         static std::default_random_engine generator(rd());
//         static std::uniform_int_distribution<int> distribution(sub, upper);
//         return std::move(distribution(generator));
//     }
//     static std::vector<int> random_ints(size_t quantity, size_t sub = 0, size_t upper = 100)
//     {
//         std::vector<int> values;
//         for (size_t i = 0; i < quantity; i++)
//         {
//             values.emplace_back(random_int());
//         }
//         return std::move(values);
//     }
//     static std::vector<std::string> readline(std::string pwd)
//     {
//         std::vector<std::string> content;
//         if (!std::filesystem::exists(pwd))
//         {
//             return content;
//         }
//         std::filesystem::directory_entry entry(pwd);
//         if (entry.status().type() == std::filesystem::file_type::directory)
//         {
//             return content;
//         }

//         std::fstream file(pwd, std::ios::in | std::ios::binary);
//         if (!file.is_open())
//         {
//             return content;
//         }

//         std::string line;
//         while (std::getline(file, line))
//         {
//             content.emplace_back(std::move(line));
//         }
//         file.close();
//         return std::move(content);
//     }
//     static int writeline(std::vector<std::string> &content, std::string pwd)
//     {
//         // if (!std::filesystem::exists(pwd))
//         // {
//         //     std::filesystem::create_directory(pwd);
//         // }

//         std::ofstream file(pwd, std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);
//         if (!file.is_open())
//         {
//             return -1;
//         }
//         for (std::string &line : content)
//         {
//             file << line << std::endl;
//         }
//         file.close();
//         return 0;
//     }
//     static std::vector<std::string> split_delim(std::string &src, std::string delim)
//     {
//         std::vector<std::string> content;
//         std::regex reg("[" + delim + "]+");
//         std::sregex_token_iterator tokens(src.cbegin(), src.cend(), reg, -1);
//         std::sregex_token_iterator end;
//         for (; tokens != end; ++tokens)
//         {
//             content.emplace_back(*tokens);
//         }
//         return content;
//     }
// };

