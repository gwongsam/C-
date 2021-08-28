#include <functional>
#include <memory>
#include <vector>
#include "../algorithms/sorting.hpp"
#include "../public/public.hpp"
#include "../algorithms/node.hpp"
using TreeNode = Node;

class Solution
{
public:
    int FindSecondMinimumValue(std::shared_ptr<TreeNode> root)
    {
        int ans = -1;
        int rootvalue = root->val;

        std::function<void(std::shared_ptr<TreeNode>)> DFS = [&](std::shared_ptr<TreeNode> node)
        {
            if (!node)
            {
                return;
            }
            if (ans != -1 && node->val >= ans)
            {
                return;
            }
            if (node->val > rootvalue)
            {
                ans = node->val;
            }
            DFS(node->left);
            DFS(node->right);
        };
        DFS(root);
        return ans;
    }
};

int main()
{
    std::vector<int> arr = Public::RandomInts(10, 0, 100000);
    Selection<int> selection;
    Insertion<int> insertion;
    Shellsort<int> shellsort;
    selection.Sorting<int>::Show(arr);
    auto start = Public::GetTimePoint();
    shellsort.Sort(arr);
    auto end = Public::GetTimePoint();
    std::cout << "Elapsed time: " << Public::GetElapsedTime(start, end) << "us" << std::endl;
    selection.Sorting<int>::Show(arr);
    return 0;
}