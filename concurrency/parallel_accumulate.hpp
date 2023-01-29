#pragma once
#include "../pch.hpp"
#include "accumulate_block.hpp"
#include "thread_pool.hpp"

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  uint64_t const length = std::distance(first, last);
  if (!length) {
    return init;
  }
  uint64_t const block_size = 25;
  uint64_t const num_blocks = (length + block_size - 1) / block_size;
  std::vector<std::future<T>> futures(num_blocks - 1);
  thread_pool pool;
  Iterator block_start = first;
  for (uint64_t i = 0; i < (num_blocks - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    futures[i] = pool.submit([=] {
      return accumulate_block<Iterator, T>()(block_start, block_end);
    });
    block_start = block_end;
  }
  T last_result = accumulate_block<Iterator, T>()(block_start, last);
  T result = init;
  for (uint64_t i = 0; i < (num_blocks - 1); ++i) {
    result += futures[i].get();
  }
  result += last_result;
  return result;
}
