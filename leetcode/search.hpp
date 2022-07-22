#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace Leetcode {
// 0542
std::vector<std::vector<int>> UpdateMatrix(
    std::vector<std::vector<int>>& matrix) {
  static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int m = matrix.size();
  int n = matrix[0].size();
  std::vector<std::vector<int>> dist(m, std::vector<int>(n, 0));
  std::vector<std::vector<int>> visited(m, std::vector<int>(n, 0));
  std::queue<std::pair<int, int>> q;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == 0) {
        q.emplace(i, j);
        visited[i][j] = 1;
      }
    }
  }
  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();
    for (int k = 0; k < 4; ++k) {
      int ni = i + dirs[k][0];
      int nj = j + dirs[k][1];
      if (0 <= ni && ni < m && 0 <= nj && nj < n && !visited[ni][nj]) {
        dist[ni][nj] = dist[i][j] + 1;
        q.emplace(ni, nj);
        visited[ni][nj] = 1;
      }
    }
  }
  return dist;
}
// 0695
int MaxAreaOfIsland(std::vector<std::vector<int>>& grid) {
  int ans = 0;
  int m = grid.size();
  int n = grid[0].size();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int currAns = 0;
      std::stack<int> stacki;
      std::stack<int> stackj;
      stacki.emplace(i);
      stackj.emplace(j);
      while (!stacki.empty()) {
        int cur_i = stacki.top();
        int cur_j = stackj.top();
        stacki.pop();
        stackj.pop();
        if (cur_i < 0 || cur_j < 0 || cur_i == m || cur_j == n ||
            grid[cur_i][cur_j] != 1) {
          continue;
        }
        currAns++;
        grid[cur_i][cur_j] = 0;
        int di[4] = {0, 0, 1, -1};
        int dj[4] = {1, -1, 0, 0};
        for (int index = 0; index < 4; index++) {
          int next_i = cur_i + di[index];
          int next_j = cur_j + dj[index];
          stacki.emplace(next_i);
          stackj.emplace(next_j);
        }
      }

      ans = std::max(ans, currAns);
    }
  }
  return ans;
}
// 0733
std::vector<std::vector<int>> FloodFill(std::vector<std::vector<int>>& image,
                                        int sr, int sc, int newColor) {
  int currColor = image[sr][sc];
  if (currColor == newColor) {
    return image;
  }
  const int dx[4] = {-1, 0, 1, 0};
  const int dy[4] = {0, -1, 0, 1};
  std::queue<std::pair<int, int>> que;
  int m = image.size();
  int n = image[0].size();
  que.emplace(sr, sc);
  image[sr][sc] = newColor;
  while (!que.empty()) {
    int x = que.front().first;
    int y = que.front().second;
    que.pop();
    for (int i = 0; i < 4; ++i) {
      int mx = x + dx[i];
      int my = y + dy[i];
      if (0 <= mx && mx < m && 0 <= my && my < n &&
          image[mx][my] == currColor) {
        que.emplace(mx, my);
        image[mx][my] = newColor;
      }
    }
  }

  return image;
}
// 0994
int OrangesRotting(std::vector<std::vector<int>>& grid) {
  static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int fresh_orange = 0;
  int ans_times = 0;
  int m = grid.size();
  int n = grid[0].size();
  std::vector<std::vector<int>> rotted(m, std::vector(n, 0));
  std::vector<std::vector<int>> visited(m, std::vector(n, 0));
  std::queue<std::pair<int, int>> q;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 2) {
        rotted[i][j] = 0;
        q.emplace(i, j);
      } else if (grid[i][j] == 1) {
        fresh_orange++;
      }
    }
  }
  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();
    visited[i][j] = 1;
    for (int k = 0; k < 4; ++k) {
      int ni = i + dirs[k][0];
      int nj = j + dirs[k][1];
      if (0 <= ni && ni < m && 0 <= nj && nj < n && !visited[ni][nj] &&
          grid[ni][nj] == 1) {
        rotted[ni][nj] = rotted[i][j] + 1;
        visited[ni][nj] = 1;
        fresh_orange--;
        ans_times = rotted[ni][nj];
        q.emplace(ni, nj);
      }
    }
    if (fresh_orange <= 0) {
      break;
    }
  }

  return fresh_orange <= 0 ? ans_times : -1;
}
}  // namespace Leetcode