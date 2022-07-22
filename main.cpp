#include <atomic>
#include <bitset>
#include <compare>
#include <coroutine>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>

#include "algorithms/digraph.hpp"
#include "algorithms/graph.hpp"
#include "algorithms/heap_priority_queue.hpp"
#include "algorithms/searching.hpp"
#include "algorithms/sorting.hpp"
#include "algorithms/string.hpp"
#include "algorithms/structure.hpp"
#include "concurrency/lock_free_stack.hpp"
#include "concurrency/thread_pool.hpp"
#include "concurrency/threadsafe_queue.hpp"
#include "concurrency/threadsafe_stack.hpp"
#include "leetcode/array.hpp"
#include "leetcode/others.hpp"
#include "leetcode/string.hpp"
#include "public/public.hpp"

using namespace std;
using namespace graph;
using namespace interface;
using namespace algo;

std::string Test() { return "Test"; }

int main() {
  std::time_t end_time =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  cout << std::ctime(&end_time) << endl;
  return 0;
}
