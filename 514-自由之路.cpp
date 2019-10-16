514. 自由之路

视频游戏“辐射4”中，任务“通向自由”要求玩家到达名为“Freedom Trail Ring”的金属表盘，并使用表盘拼写特定关键词才能开门。

给定一个字符串 ring，表示刻在外环上的编码；给定另一个字符串 key，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数。

最初，ring 的第一个字符与12:00方向对齐。您需要顺时针或逆时针旋转 ring 以使 key 的一个字符在 12:00 方向对齐，然后按下中心按钮，以此逐个拼写完 key 中的所有字符。

旋转 ring 拼出 key 字符 key[i] 的阶段中：

您可以将 ring 顺时针或逆时针旋转一个位置，计为1步。旋转的最终目的是将字符串 ring 的一个字符与 12:00 方向对齐，并且这个字符必须等于字符 key[i] 。
如果字符 key[i] 已经对齐到12:00方向，您需要按下中心按钮进行拼写，这也将算作 1 步。按完之后，您可以开始拼写 key 的下一个字符（下一阶段）, 直至完成所有拼写。
示例：

 //图像见 https://leetcode-cn.com/problems/freedom-trail/


 
输入: ring = "godding", key = "gd"
输出: 4
解释:
对于 key 的第一个字符 'g'，已经在正确的位置, 我们只需要1步来拼写这个字符。
对于 key 的第二个字符 'd'，我们需要逆时针旋转 ring "godding" 2步使它变成 "ddinggo"。
当然, 我们还需要1步进行拼写。
因此最终的输出是 4。

/*
首先经过验证，贪心是不对的。还是要考虑使用dp来解这个问题。
dp[i][j] 表示，在满足匹配 0 - i 的key位置，且最后一个位置 ring 落在 j 位置时候，所需要的最小步数。
当key[i] != ring[j] 时，说明dp[i][j] 不可能真正对上，这时候 dp[i][j] = INT_MAX
当 key[i] == ring[j] 时，我们要找到 ring 的位置k，使得 key[i-1] 和 ring[k] 可以对上，这里是一个起始点，
    然后计算从 k 移动到 j 所花费的最短距离 + dp[i-1][k]。遍历找到所有满足条件的k，计算最小值。
最后，计算所有key[end] == ring[j] 时， dp[end][j]，找到其中的最小值。


*/
int findRotateSteps(string ring, string key) {
    int n = ring.size(), m = key.size();
    int res = INT_MAX;
    vector<vector<int>> dp(m, vector<int>(n, INT_MAX));// 初始化全都是INT_MAX
    for(int j = 0; j < n; j++){
        if(key[0] == ring[j])
            dp[0][j] = min(n - j, j) + 1; //找到距离数组两个端点最近的距离
    }
    for(int i = 1; i < m; i++){
        for(int j =  0; j < n; j++){
            if(key[i] != ring[j]) continue;//结果对比上，只能是INT_MAX
            for(int k = 0; k < n; k++){//遍历计算上一次的结果
                if(key[i-1] != ring[k]) continue;
                dp[i][j] = min(dp[i][j], dp[i-1][k] + min((j-k+n)%n, (k-j+n)%n) + 1);//计算从k 到 j 的最短距离，然后求总体最短。
            }
        }
    }
    //计算最后的结果
    for(int j = 0; j < n; j++){
        if(key[m-1] != ring[j]) continue;
        res = min(res, dp[m-1][j]);
    }
    return res;
}