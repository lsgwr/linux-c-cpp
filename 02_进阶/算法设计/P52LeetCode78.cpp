/***********************************************************
 * @Description : Solution解题模板
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/12/2 23:07
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> ans;

    vector<vector<int>> subsets(vector<int> &nums) {
        ans.emplace_back();
        for (int i = 0; i < nums.size(); i++) {
            vector<int> visited(nums.size(), 0); // 初始化为0，表示没被访问过
            vector<int> result;
            dfs(nums, result, visited, i); // 从当前节点开始遍历
        }
        return ans;
    }

    void dfs(vector<int> &nums, vector<int> &result, vector<int> &visited, int index) {
        visited[index] = 1;
        result.push_back(nums[index]);
        ans.push_back(result);

        for (int i = index + 1; i < nums.size(); i++) {
            if (!visited[i]) {
                dfs(nums, result, visited, i); // 找到没遍历到的元素，进行下一轮
                result.pop_back();
                visited[i] = 0;
            }
        }
    }
};

int main() {
    int a[] = {1, 2, 3};
    vector<int> nums(a, a + 3);
    Solution s;
    auto result = s.subsets(nums);
    return 0;
}