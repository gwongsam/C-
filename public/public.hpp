#pragma once
#include <chrono>
#include <codecvt>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <regex>
#include <string>
#include <vector>

namespace aux {
template <typename Number>
Number Random(long long sub = 0, long long upper = 100) {
  static std::random_device rd;
  static std::default_random_engine generator(rd());

  std::uniform_int_distribution<Number> distribution(sub, upper);
  return distribution(generator);
}

template <typename Number>
std::vector<Number> Randoms(size_t quantity, long long sub = 0,
                            long long upper = 100) {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<Number> distribution(sub, upper);

  std::vector<Number> values;
  for (size_t i = 0; i < quantity; i++) {
    values.push_back(distribution(generator));
  }
  return std::move(values);
}

int RandomInt(size_t sub = 0, size_t upper = 100) {
  static std::random_device rd;
  static std::default_random_engine generator(rd());
  static std::uniform_int_distribution<int> distribution(sub, upper);
  return std::move(distribution(generator));
}

std::vector<int> RandomInts(size_t quantity, size_t sub = 0,
                            size_t upper = 100) {
  std::vector<int> values;
  for (size_t i = 0; i < quantity; i++) {
    values.emplace_back(RandomInt(sub, upper));
  }
  return std::move(values);
}

std::vector<std::string> ReadLines(std::string pwd) {
  std::vector<std::string> content;
  if (!std::filesystem::exists(pwd)) {
    return content;
  }
  std::filesystem::directory_entry entry(pwd);
  if (entry.status().type() == std::filesystem::file_type::directory) {
    return content;
  }

  std::fstream file(pwd, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    return content;
  }

  std::string line;
  while (std::getline(file, line)) {
    content.emplace_back(std::move(line));
  }
  file.close();
  return std::move(content);
}

int WriteLines(std::vector<std::string> &content, std::string pwd) {
  std::filesystem::path dir = pwd;
  if (!std::filesystem::exists(dir.parent_path())) {
    std::filesystem::create_directory(dir.parent_path());
  }

  std::ofstream file(
      pwd, std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);
  if (!file.is_open()) {
    return -1;
  }
  for (std::string &line : content) {
    file << line << std::endl;
  }
  file.close();
  return 0;
}

std::vector<std::string> SplitDelim(std::string &src, std::string delim) {
  std::vector<std::string> content;
  std::regex reg(delim);
  std::sregex_token_iterator tokens(src.cbegin(), src.cend(), reg, -1);
  std::sregex_token_iterator end;
  for (; tokens != end; ++tokens) {
    content.emplace_back(*tokens);
  }
  return std::move(content);
}

std::string FileToString(std::string pwd) {
  if (!std::filesystem::exists(pwd)) {
    return "";
  }
  std::ifstream ifs(pwd);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  return std::move(content);
}

bool IsAlphabet(const char a) {
  return ('a' <= a && a <= 'z') || ('A' <= a && a <= 'Z');
}

std::string w2s(const std::wstring &wide) {
  std::string str;
  std::transform(wide.begin(), wide.end(), std::back_inserter(str),
                 [](unsigned short c) { return char(c); });
  return str;
  // static std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
  // return std::move(myconv.to_bytes(wide));
}

std::wstring s2w(const std::string &str) {
  static std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
  return myconv.from_bytes(str);
}

class IO {
 public:
  static std::vector<std::string> ReadLines(std::string pwd) {
    std::vector<std::string> content;
    if (!std::filesystem::exists(pwd)) {
      return content;
    }
    std::filesystem::directory_entry entry(pwd);
    if (entry.status().type() == std::filesystem::file_type::directory) {
      return content;
    }

    std::fstream file(pwd, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
      return content;
    }

    std::string line;
    while (std::getline(file, line)) {
      content.emplace_back(std::move(line));
    }
    file.close();
    return std::move(content);
  }
  static int WriteLines(std::vector<std::string> &content, std::string pwd) {
    // if (!std::filesystem::exists(pwd))
    // {
    //     std::filesystem::create_directory(pwd);
    // }

    std::ofstream file(
        pwd, std::ios::out | std::ios::binary | std::ios::app | std::ios::ate);
    if (!file.is_open()) {
      return -1;
    }
    for (std::string &line : content) {
      file << line << std::endl;
    }
    file.close();
    return 0;
  }
};
}  // namespace aux

namespace aux {
class StopWatch {
 public:
  std::chrono::steady_clock::time_point Start() {
    start_ = std::chrono::steady_clock::now();
    return start_;
  }
  std::chrono::steady_clock::time_point Stop() {
    end_ = std::chrono::steady_clock::now();
    return end_;
  }
  long long ElapsedMilliseconds() {
    long long elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_)
            .count();
    return elapsed;
  }
  long long ElapsedMicroseconds() {
    long long elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_)
            .count();
    return elapsed;
  }

 private:
  std::chrono::steady_clock::time_point start_;
  std::chrono::steady_clock::time_point end_;
};
}  // namespace aux
