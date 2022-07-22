
#include <filesystem>
#include <iostream>

#include "../public/public.hpp"
#include "array.hpp"
#include "string.hpp"
using namespace std;

int main() {
  auto nums = aux::Randoms<int>(10, 0, 10);
  Quicksort<int> qs;
  return 0;
}