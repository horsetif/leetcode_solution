516. 最长回文子序列
给定一个字符串s，找到其中最长的回文子序列。可以假设s的最大长度为1000。

示例 1:
输入:

"bbbbab"
输出:

4
一个可能的最长回文子序列为 "bbbb"。

示例 2:
输入:

"cbbd"
输出:

2
一个可能的最长回文子序列为 "bb"。

/*
dp问题。设dp[i][j] 表示为 从字符串位置 i 到 位置 j 的最长回文的长度。
如果 s[i] == s[j] 那么 dp[i][j] = dp[i+1][j-1] + 2
如果 s[i] != s[j] 那么 dp[i][j] = max(dp[i+1][j], dp[i][j-1])
初始化 dp[i][i] = 1，最后计算 dp[0][n-1]
在优化过程中，i 从后往前找，j 从 i 后面 开始往后找.
*/
int longestPalindromeSubseq(string s) {
    int n = s.size();
    if(n == 0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) dp[i][i] = 1;
    for(int i = n - 1; i >= 0; i--){
        for(int j = i + 1; j < n; j ++){
            if(s[i] == s[j])
                dp[i][j] = dp[i+1][j-1] + 2;//相同条件下，同时收缩
            else
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);//不同条件下，只收缩一边
        }
    }
    return dp[0][n-1];
}