#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

namespace Leetcode {
// 0001
std::vector<int> TwoSum(std::vector<int> &nums, int target) {
  std::unordered_map<int, int> hashtable;
  for (int i = 0; i < nums.size(); i++) {
    auto it = hashtable.find(target - nums[i]);
    if (it != hashtable.end()) {
      return {it->second, i};
    }
    hashtable[nums[i]] = i;
  }
  return {};
}
// 0011
int MaxArea(std::vector<int> &height) {
  int left = 0, right = height.size() - 1;
  int ans = 0;
  while (left < right) {
    int area = std::min(height[left], height[right]) * (right - left);
    ans = std::max(ans, area);
    if (height[left] <= height[right]) {
      ++left;
    } else {
      --right;
    }
  }
  return ans;
}
// 0015
std::vector<std::vector<int>> ThreeSum(std::vector<int> &nums) {
  int n = nums.size();
  std::sort(nums.begin(), nums.end());
  std::vector<std::vector<int>> ans;
  for (int first = 0; first < n; ++first) {
    if (first > 0 && nums[first] == nums[first - 1]) {
      continue;
    }
    int third = n - 1;
    int target = -nums[first];
    for (int second = first + 1; second < n; ++second) {
      if (second > first + 1 && nums[second] == nums[second - 1]) {
        continue;
      }
      while (second < third && nums[second] + nums[third] > target) {
        --third;
      }
      if (second == third) {
        break;
      }
      if (nums[second] + nums[third] == target) {
        ans.push_back({nums[first], nums[second], nums[third]});
      }
    }
  }

  return ans;
}
// 0018
std::vector<std::vector<int>> FourSum(std::vector<int> &nums, int target) {
  std::vector<std::vector<int>> quadruplets;
  if (nums.size() < 4) {
    return quadruplets;
  }
  std::sort(nums.begin(), nums.end());
  size_t count = nums.size();
  for (size_t i = 0; i < count - 3; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    if ((long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
      break;
    }
    if ((long)nums[i] + nums[count - 3] + nums[count - 2] + nums[count - 1] <
        target) {
      continue;
    }
    for (size_t j = 0; j < count - 2; j++) {
      if (j > i + 1 && nums[j] == nums[j - 1]) {
        continue;
      }
      if ((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
        break;
      }
      if ((long)nums[i] + nums[j] + nums[count - 2] + nums[count - 1] <
          target) {
        continue;
      }
      size_t left = j + 1;
      size_t right = count - 1;
      while (left < right) {
        int sum = nums[i] + nums[j] + nums[left] + nums[right];
        if (sum == target) {
          quadruplets.push_back({nums[i], nums[j], nums[left], nums[right]});
          while (left < right && nums[left] == nums[left + 1]) {
            left++;
          }
          left++;
          while (left < right && nums[right] == nums[right - 1]) {
            right--;
          }
          right--;
        } else if (sum < target) {
          left++;
        } else {
          right--;
        }
      }
    }
  }
  return quadruplets;
}
// 0026
int RemoveDuplicate(std::vector<int> &nums) {
  size_t count = nums.size();
  if (count == 0) {
    return 0;
  }
  size_t fast = 1;
  size_t slow = 1;
  while (fast < count) {
    if (nums[fast] != nums[fast - 1]) {
      nums[slow++] = nums[fast];
    }
    ++fast;
  }
  return slow;
}
// 0027
int RemoveElement(std::vector<int> &nums, int val) {
  size_t left = 0;
  size_t right = nums.size();
  while (left < right) {
    if (nums[left] == val) {
      nums[left] = nums[right - 1];
      right--;
    } else {
      left++;
    }
  }
  return left;
}
// 0031
void NextPermutation(std::vector<int> &nums) {
  int i = nums.size() - 2;
  while (i >= 0 && nums[i] >= nums[i + 1]) {
    i--;
  }
  if (i > 0) {
    int j = nums.size() - 1;
    while (j >= 0 && nums[i] >= nums[j]) {
      j--;
    }
    std::swap(nums[i], nums[j]);
  }
  std::reverse(nums.begin() + i + 1, nums.end());
}
// 0033
int SearchRotated(std::vector<int> &nums, int target) {
  if (nums.empty()) {
    return -1;
  } else if (nums.size() == 1) {
    return nums[0] == target ? 0 : -1;
  }
  size_t left = 0;
  size_t right = nums.size() - 1;
  while (left <= right) {
    size_t pivot = (left + right) / 2;
    if (nums[pivot] == target) {
      return pivot;
    }
    if (nums[0] <= nums[pivot]) {
      if (nums[0] <= target && target < nums[pivot]) {
        right = pivot - 1;
      } else {
        left = pivot + 1;
      }
    } else {
      if (nums[pivot] < target && target <= nums[nums.size() - 1]) {
        left = pivot + 1;
      } else {
        right = pivot - 1;
      }
    }
  }

  return -1;
}
// 0034
std::vector<int> SearchRange(std::vector<int> nums, int target) {
  if (nums.empty()) {
    return {-1, -1};
  } else if (nums.size() == 1) {
    if (nums[0] == target) {
      return {0, 0};
    } else {
      return {-1, -1};
    }
  }
  int left = 0;
  int right = nums.size() - 1;
  while (left <= right) {
    int pivot = (left + right) / 2;
    if (nums[pivot] == target) {
      int sub = pivot;
      int upper = pivot;
      while (sub > 0) {
        if (nums[sub - 1] == target) {
          sub -= 1;
        } else {
          break;
        }
      }
      while (upper < nums.size() - 1) {
        if (nums[upper + 1] == target) {
          upper += 1;
        } else {
          break;
        }
      }

      return {sub, upper};
    } else if (nums[pivot] < target) {
      left = pivot + 1;
    } else {
      right = pivot - 1;
    }
  }

  return {-1, -1};
}
// 0035
int SearchInsert(std::vector<int> &nums, int target) {
  int count = nums.size();
  int left = 0, right = count - 1;
  int ans = count;
  while (left <= right) {
    int mid = ((right - left) >> 1) + left;
    if (nums[mid] < target) {
      left = mid + 1;
    } else {
      ans = mid;
      right = mid - 1;
    }
  }
  return ans;
}
// 0036
bool IsValidSudoku(std::vector<std::vector<char>> &board) {
  int rows[9][9];
  int columns[9][9];
  int subboxes[3][3][9];
  // memset(rows, 0, sizeof(rows));
  // memset(columns, 0, sizeof(columns));
  // memset(subboxes, 0, sizeof(subboxes));

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      char c = board[i][j];
      if (c != '.') {
        int index = c - '0' - 1;
        rows[i][index]++;
        columns[j][index]++;
        subboxes[i / 3][j / 3][index]++;
        if (rows[i][index] > 1 || columns[j][index] > 1 ||
            subboxes[i / 3][j / 3][index] > 1) {
          return false;
        }
      }
    }
  }
  return true;
}
// 0039
// class CombinationSum {
//  public:
//   std::vector<std::vector<int>> Sum(std::vector<int> &candidates, int target)
//   {
//     std::vector<std::vector<int>> ans;
//     std::vector<std::vector<int>> combine;
//     DFS(candidates, target, ans, combine, 0);
//     return ans;
//   }

//   void DFS(std::vector<int> &candidates, int target,
//            std::vector<std::vector<int>> &ans,
//            std::vector<std::vector<int>> &combine, int idx) {
//     if (idx == candidates.size()) {
//       return;
//     }
//     if (target == 0) {
//       ans.push_back(combine);
//       return;
//     }
//     DFS(candidates, target, ans, combine, idx + 1);
//     if (target - candidates[idx] >= 0) {
//       combine.emplace_back(candidates[idx]);
//       DFS(candidates, target - candidates[idx], ans, combine, idx);
//       combine.pop_back();
//     }
//   }
// };
// 0048
void RotateImage(std::vector<std::vector<int>> &matrix) {
  int n = matrix.size();
  for (int i = 0; i < n / 2; ++i) {
    for (int j = 0; j < (n + 1) / 2; ++j) {
      int temp = matrix[i][j];
      matrix[i][j] = matrix[n - j - 1][i];
      matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
      matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
      matrix[j][n - i - 1] = temp;
    }
  }
}
// 0054
std::vector<int> SpiralOrder(std::vector<std::vector<int>> &matrix) {
  if (matrix.size() == 0 || matrix[0].size() == 0) {
    return {};
  }
  int rows = matrix.size();
  int columns = matrix[0].size();
  std::vector<int> order;
  int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
  while (left <= right && top <= bottom) {
    for (int column = left; column <= right; column++) {
      order.emplace_back(matrix[top][column]);
    }
    for (int row = top + 1; row <= bottom; row++) {
      order.emplace_back(matrix[row][right]);
    }
    if (left < right && top < bottom) {
      for (int column = right - 1; column > left; column--) {
        order.emplace_back(matrix[bottom][column]);
      }
      for (int row = bottom; row > top; row--) {
        order.emplace_back(matrix[row][left]);
      }
    }
    left++;
    right--;
    top++;
    bottom--;
  }
  return order;
}
// 0045
int JumpGame(std::vector<int> &nums) {
  int maxPos = 0;
  int count = nums.size();
  int end = 0;
  int step = 0;
  for (int i = 0; i < count - 1; i++) {
    if (maxPos >= i) {
      maxPos = std::max(maxPos, i + nums[i]);
      if (i == end) {
        end == maxPos;
        ++step;
      }
    }
  }
  return step;
}
// 0053
int MaxSubArray(std::vector<int> &nums) {
  int pre = 0;
  int ans = nums[0];
  for (int i = 0; i < nums.size(); i++) {
    pre = std::max(pre + nums[i], nums[i]);
    ans = std::max(pre, ans);
  }

  return ans;
}
// 0055
bool CanJump(std::vector<int> &nums) {
  int maxPos = 0;
  int count = nums.size();
  for (int i = 0; i < count; ++i) {
    if (i <= maxPos) {
      maxPos = std::max(maxPos, i + nums[i]);
      if (maxPos >= count - 1) {
        return true;
      }
    }
  }
  return false;
}
// 0056
std::vector<std::vector<int>> Merge(std::vector<std::vector<int>> &intervals) {
  std::vector<std::vector<int>> ans;
  if (intervals.size() == 0) {
    return ans;
  }
  std::sort(intervals.begin(), intervals.end());
  for (int i = 0; i < intervals.size(); i++) {
    int L = intervals[i][0];
    int R = intervals[i][1];
    if (!ans.size() || ans.back()[1] < L) {
      ans.push_back({L, R});
    } else {
      ans.back()[1] = std::max(ans.back()[1], R);
    }
  }
  return ans;
}
// 0073
void SetZeroes(std::vector<std::vector<int>> &matrix) {
  int m = matrix.size();
  int n = matrix[0].size();
  bool flag_col = false;
  for (int i = 0; i < m; ++i) {
    if (!matrix[i][0]) {
      flag_col = true;
    }
    for (int j = 1; j < n; ++j) {
      if (!matrix[i][j]) {
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }
    }
  }
  for (int i = m - 1; i >= 0; --i) {
    for (int j = 1; j < n; ++j) {
      if (!matrix[i][0] || !matrix[0][j]) {
        matrix[i][j] = 0;
      }
    }
    if (flag_col) {
      matrix[i][0] = 0;
    }
  }
}
// 0077
std::vector<std::vector<int>> CombineKNums(int n, int k) {
  std::vector<std::vector<int>> ans;

  return ans;
}
void MergeSortedArray(std::vector<int> &nums1, int m, std::vector<int> &nums2,
                      int n) {
  int count = m + n;
  for (int i = count - 1; i >= 0; --i) {
    if (n - 1 < 0) {
      nums1[i] = nums1[--m];
    } else if (m - 1 < 0) {
      nums1[i] = nums2[--n];
    } else if (nums1[m - 1] > nums2[n - 1]) {
      nums1[i] = nums1[--m];
    } else {
      nums1[i] = nums2[--n];
    }
  }
}
// 0118
std::vector<std::vector<int>> PascalsTriangle(int numRows) {
  std::vector<std::vector<int>> ans(numRows);
  for (int i = 0; i < numRows; ++i) {
    ans[i].resize(i + 1);
    ans[i][0] = ans[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      ans[i][j] = ans[i - 1][j] + ans[i - 1][j - 1];
    }
  }
  return ans;
}
// 0121
int MaxProfit(std::vector<int> &prices) {
  int max_profit = 0;
  int min_price = prices[0];
  for (auto price : prices) {
    int profit = price - min_price;

    if (price < min_price) {
      min_price = price;
    } else if (profit > max_profit) {
      max_profit = profit;
    }
  }
  return max_profit;
}
// 0167
std::vector<int> TwoSum2(std::vector<int> &nums, int target) {
  for (int left = 0, right = nums.size() - 1; left < right;) {
    int sum = nums[left] + nums[right];
    if (sum > target) {
      --right;
    } else if (sum < target) {
      ++left;
    } else {
      return {left + 1, right + 1};
    }
  }
  return {};
}
// 0189
void RotateArray(std::vector<int> &nums, int k) {
  auto reverse = [](std::vector<int> &nums, int start, int end) {
    while (start < end) {
      std::swap(nums[start++], nums[end--]);
    }
  };
  k %= nums.size();
  reverse(nums, 0, nums.size() - 1);
  reverse(nums, 0, k - 1);
  reverse(nums, k, nums.size() - 1);
  // int n = nums.size();
  // std::vector<int> newArr(n);
  // for (int i = 0; i < n; ++i) {
  //   newArr[(i + k) % n] = nums[i];
  // }
  // nums.assign(newArr.begin(), newArr.end());
}
// 0258
int AddDigits(int num) { return (num - 1) % 9 + 1; }
// 0278
int FirstBadVersion(int n) {
  int left = 1;
  int right = n;
  auto isBadVersion = [](int n) { return aux::Random<int>(0, 2 * n) > n; };
  while (left < right) {
    int mid = ((right - left) >> 1) + left;
    if (isBadVersion(mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}
// 0283
void MoveZeros(std::vector<int> &nums) {
  for (int slow = 0, fast = 0; fast < nums.size(); ++fast) {
    if (nums[fast] != 0) {
      std::swap(nums[slow++], nums[fast]);
    }
  }
}
// 0350
std::vector<int> Intersect(std::vector<int> &nums1, std::vector<int> &nums2) {
  std::vector<int> ans;
  if (nums1.size() > nums2.size()) {
    return Intersect(nums2, nums1);
  }
  std::unordered_map<int, int> m;
  for (auto item : nums1) {
    m[item]++;
  }
  for (auto item : nums2) {
    if (m.count(item)) {
      ans.emplace_back(item);
      m[item]--;
      if (m[item] == 0) {
        m.erase(item);
      }
    }
  }

  return ans;
}
// 0566
std::vector<std::vector<int>> MatrixReshape(std::vector<std::vector<int>> &mat,
                                            int r, int c) {
  int m = mat.size();
  int n = mat[0].size();
  if (m * n != r * c) {
    return mat;
  }
  std::vector<std::vector<int>> ans(r, std::vector<int>(c));
  int count = m * n;
  for (int i = 0; i < m * n; ++i) {
    ans[i / c][i % c] = mat[i / n][i % n];
  }
  return ans;
}
// 0704
int Bisearch(std::vector<int> &nums, int target) {
  int left = 0;
  int right = nums.size() - 1;
  while (left <= right) {
    // int mid = (left + right) / 2;
    int mid = ((right - left) >> 1) + left;
    if (target < nums[mid]) {
      right = mid - 1;
    } else if (target > nums[mid]) {
      left = mid + 1;
    } else {
      return mid;
    }
  }

  return -1;
}
// 2016
int MaximumDifference(std::vector<int> &nums) {
  size_t count = nums.size();
  int ans = -1, premin = nums[0];
  for (size_t i = 1; i < count; ++i) {
    if (nums[i] > premin) {
      ans = std::max(ans, nums[i] - premin);
    } else {
      premin = nums[i];
    }
  }
  return ans;
}
// 1991
int FindMiddleIndex(std::vector<int> &nums) {
  int total = std::accumulate(nums.begin(), nums.end(), 0);
  int sum = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (2 * sum + nums[i] == total) {
      return i;
    }
    sum += nums[i];
  }
  return 0;
}
void LongestChain() {
  vector<string> index{"3", "4", "5", "6", "7", "8", "9", "10",
                       "J", "Q", "K", "A", "2", "B", "C"};
  unordered_map<string, int> cards;
  for (int i = 0; i < 15; ++i) {
    if (i >= 13) {
      cards.emplace(index[i], 1);
    } else {
      cards.emplace(index[i], 4);
    }
  }
  vector<string> used;
  vector<string> host;

  int begin_ = 0;
  int end_ = 0;
  int begin = 14;
  int end = 14;
  int longest = 0;
  for (int i = 14; i >= 0; --i) {
    if (cards[index[i]] == 0) {
      begin = i - 1;
      end = i - 1;
      continue;
    }
    end -= 1;
    if (begin - end + 1 >= 5 && begin - end + 1 > longest) {
      begin_ = begin;
      end_ = end;
      longest = begin_ - end_ + 1;
    }
  }
  if (longest >= 5) {
    if (longest >= 12) {
      longest = 12;
    }
    for (int i = end_; i < end_ + longest - 1; ++i) {
      cout << index[i];
    }
  } else {
    cout << "NO_CHAIN";
  }
}
// 0977
std::vector<int> SortedSquares(std::vector<int> nums) {
  std::vector<int> ans(nums.size());
  for (int left = 0, right = nums.size() - 1, i = nums.size() - 1;
       left <= right; i--) {
    int a = std::pow(nums[left], 2);
    int b = std::pow(nums[right], 2);
    if (a > b) {
      ans[i] = a;
      left++;
    } else {
      ans[i] = b;
      right--;
    }
  }
  return ans;
}

}  // namespace Leetcode
