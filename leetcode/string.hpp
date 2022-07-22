#pragma once
#include <string>
#include <unordered_set>
#include <vector>

#include "../public/public.hpp"

namespace Leetcode {
// 0003
int LengthOfLongestSubstring(std::string s) {
  std::unordered_set<char> occ;
  int n = s.size();
  int rk = -1;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (i != 0) {
      occ.erase(s[i - 1]);
    }
    while (rk + 1 < n && !occ.count(s[rk + 1])) {
      occ.insert(s[rk + 1]);
      ++rk;
    }
    ans = std::max(ans, rk - i + 1);
  }
  return ans;
}
// 0005
std::string LogestPalindrome(const std::string& s) {
  int n = s.size();
  if (n < 2) {
    return s;
  }
  int maxLen = 1;
  int begin = 0;
  std::vector<std::vector<int>> dp(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = true;
  }
  for (int L = 2; L <= n; L++) {
    for (int i = 0; i < n; i++) {
      int j = L + i + 1;
      if (j >= n) {
        break;
      }

      if (s[i] != s[j]) {
        dp[i][j] = false;
      } else {
        if (j - i < 3) {
          dp[i][j] = true;
        } else {
          dp[i][j] = dp[i + 1][j - 1];
        }
      }

      if (dp[i][j] && j - i + 1 > maxLen) {
        maxLen = j - i + 1;
        begin = i;
      }
    }
  }
  return s.substr(begin, maxLen);
}
// 0014
std::string LongestCommonPrefix(std::vector<std::string>& strs) {
  if (strs.empty()) {
    return "";
  }
  for (int i = 0; i < strs[0].size(); ++i) {
    char c = strs[0][i];
    for (int j = 0; j < strs.size(); ++j) {
      if (strs[j].size() == i || strs[j][i] != c) {
        return strs[0].substr(0, i);
      }
    }
  }
  return strs[0];
}
// 0344
void ReverseString(std::vector<char>& s) {
  int n = s.size();
  for (int i = 0; i < n / 2; ++i) {
    std::swap(s[i], s[n - i - 1]);
  }
}
// 0521
int FindLUSlength(std::string a, std::string b) {
  return a != b ? std::max(a.length(), b.length()) : -1;
}
// 0557
std::string ReverseWords(std::string s) {
  auto reverse = [](std::string& s, int start, int end) {
    while (start < end) {
      std::swap(s[start++], s[end--]);
    }
  };
  for (int start = 0, end = 0; end <= s.size(); end++) {
    if (s[end] == ' ' || end == s.size()) {
      reverse(s, start, end - 1);
      start = end + 1;
    }
  }
  return s;
}
// 0917
std::string ReverseOnlyLetters(std::string s) {
  size_t left = 0;
  size_t right = s.size() - 1;
  while (true) {
    while (left < right && !aux::IsAlphabet(s[left])) {
      left++;
    }
    while (right > left && !aux::IsAlphabet(s[right])) {
      right--;
    }
    if (left >= right) {
      break;
    }
    std::swap(s[left++], s[right--]);
  }
  return s;
}

std::string ZConvert(std::string s, int numRows) {
  int n = s.length();
  int r = numRows;
  if (r == 1 || r >= n) {
    return s;
  }
  std::string ans;
  int t = r * 2 - 2;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j + 1 < n; j += t) {
      ans += s[j + i];
      if (0 < i && i < r - 1 && j + t - i < n) {
        ans += s[j + t - t];
      }
    }
  }
  return ans;
}
// 2045
std::vector<int> PlateBetweenCandles(std::string s,
                                     std::vector<std::vector<int>>& queries) {
  int count = s.length();
  std::vector<int> preSum(count);
  for (int i = 0, sum = 0; i < count; i++) {
    if (s[i] == '*') {
      sum++;
    }
    preSum[i] = sum;
  }
  std::vector<int> left(count);
  for (int i = 0, l = -1; i < count; i++) {
    if (s[i] == '|') {
      l = i;
    }
    left[i] = l;
  }
  std::vector<int> right(count);
  for (int i = count - 1, r = -1; i >= 0; i--) {
    if (s[i] == '|') {
      r = i;
    }
    right[i] = r;
  }
  std::vector<int> ans;
  for (auto& query : queries) {
    int x = right[query[0]], y = left[query[1]];
    ans.emplace_back(x == -1 || y == -1 ? 0 : preSum[y] - preSum[x]);
  }
  return ans;
}

void Substring() {
  std::string str1;
  std::string str2;
  cin >> str1;
  cout << endl;
  cin >> str2;
  vector<int> alphabet(26, 0);
  for (char c : str1) {
    alphabet[c - 'a']++;
  }

  int begin = 0;
  for (int i = 0; i < str2.size(); ++i) {
    if (str1.find(str2[i]) == string::npos) {
      begin = i + 1;
      continue;
    }

    if (i - begin + 1 == str1.size()) {
      vector<int> temp_table(26, 0);
      for (int j = begin; j <= i; j++) {
        temp_table[str2[j] - 'a']++;
      }
      bool matched = true;
      for (int j = 0; j < 26; ++j) {
        int t = temp_table[j];
        int a = alphabet[j];
        if (temp_table[j] != alphabet[j]) {
          matched = false;
          break;
        }
      }
      if (matched) {
        cout << begin;
        return;
      }
      begin++;
    }
  }
}

}  // namespace Leetcode