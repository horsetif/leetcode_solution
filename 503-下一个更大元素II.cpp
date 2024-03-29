503. 下一个更大元素 II
给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。

示例 1:

输入: [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数；
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。


//假如不是一个循环的数组，那么我们直接可以使用单调栈的思路来做。
//我们这里是单调栈，我们可以直接把数组翻倍，[a1,a2,a3,a1,a2,a3]
//然后再利用单调栈的思路，但是这里我们只关注前面三位数字。
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 0);
    stack<int> st;//设置单调栈
    for(int i = 2*n - 1; i >= 0; i--){//这里假设双倍数组
        while(!st.empty() && st.top() <= nums[i%n])//只保留最大值
            st.pop();
        res[i%n] = st.empty() ? -1 : st.top();
        st.push(nums[i%n]);
    }
    return res;
}