518. 零钱兑换 II
给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 

 

示例 1:

输入: amount = 5, coins = [1, 2, 5]
输出: 4
解释: 有四种方式可以凑成总金额:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
示例 2:

输入: amount = 3, coins = [2]
输出: 0
解释: 只用面额2的硬币不能凑成总金额3。
示例 3:

输入: amount = 10, coins = [10]
输出: 1
 

/*
思路1：回溯遍历。更深层次遍历的节点，只能大于等于浅层次遍历的节点。 -- 但是，这里会超时。
*/
/*
int change(int amount, vector<int>& coins) {
    int ind = 0, n = coins.size();
    if(n == 0) return 0;
    int res = 0 ,cur_sum = 0 ;
    sort(coins.begin(), coins.end());
    find(amount, coins, res, ind);
    return res;
}
void find(int amount, vector<int>& coins, int &res, int ind){
    if(amount == 0){
        res ++;
        return ;
    }
    for(int i = ind; i < coins.size(); i++){
        if(amount >= coins[i]){
            find(amount - coins[i], coins, res, i);
        }
        else break;
    }
    return;
}
*/
/*
思路2：背包问题。设dp[i][j] 表示：[0,i-1]个硬币，凑成总数为j的情况。
下面公式代表：放置 0 到 k 个 coin[i-1] 硬币之后，放之前的硬币，可以凑成的情况。
dp[i][j] = dp[i-1][j - 0 * coin[i-1]] + dp[i-1][j - 1 * coin[i-1]] + dp[i-1][j - 1 * coin[i-1]] + ... dp[i-1][j - k * coin[i-1]]
同时，简化后，可得: dp[i][j] = dp[i-1][j] + dp[i][j - coin[i-1]]。这个公式代表，不包括coin[i-1] 的情况，以及 一定包括 至少一个coin[i-1] 情况的总和。
*/
int change(int amount, vector<int> &coins){
    int n =  coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1,0));
    dp[0][0] = 1;//在没有硬币但是也不需要任何钱的情况下，有一种情况。这也是所有情况的起始情况。
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= amount; j++){
            dp[i][j] = dp[i-1][j];
            if(j - coins[i - 1] >= 0)
                dp[i][j] += dp[i][j - coins[i - 1]];
        }
    }
    return dp[n][amount];
}