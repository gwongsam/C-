#include <iostream>
#include <atomic>
#include "concurrency/threadsafe_stack.hpp"
#include "concurrency/lock_free_stack.hpp"
#include "algorithms/searching.hpp"
#include "algorithms/sorting.hpp"
#include "algorithms/structure.hpp"
#include "public/public.hpp"
#include <list>
#include <string>

using namespace std;

int main()
{
    // std::vector<int> arr = Public::RandomInts(10, 0, 100000);
    // Selection<int> selection;
    // Insertion<int> insertion;
    // Shellsort<int> shellsort;
    // Mergesort<int> mergesort;
    // Quicksort<int> quicksort;
    // selection.Sorting<int>::Show(arr);
    // auto start = Public::GetTimePoint();
    // quicksort.Sort(arr);
    // auto end = Public::GetTimePoint();
    // std::cout << "Elapsed time: " << Public::GetElapsedTime(start, end) << "us" << std::endl;
    // selection.Sorting<int>::Show(arr);
    std::shared_ptr<Node<size_t, std::string>> root = std::make_shared<Node<size_t, std::string>>(1, "root");
    root->left = std::make_shared<Node<size_t, std::string>>(2, "left");
    root->right = std::make_shared<Node<size_t, std::string>>(2, "right");
    root->left->left = std::make_shared<Node<size_t, std::string>>(3, "left2");
    root->left->right = std::make_shared<Node<size_t, std::string>>(4, "right2");
    root->left->right->left = std::make_shared<Node<size_t, std::string>>(5, "left3");
    Bitree<size_t, std::string> bitree;
    bitree.DFS([](std::string &val){ std::cout << val << std::endl; return;}, root);
    BST<size_t, std::string> bst;
    bst.root = root;
    std::string val;
    if (bst.Get(3, val))
    {
        std::cout << "3 " << val << std::endl;
    }
    return 0;
}
