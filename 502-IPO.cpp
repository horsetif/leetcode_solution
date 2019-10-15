502. IPO
假设 力扣（LeetCode）即将开始其 IPO。为了以更高的价格将股票卖给风险投资公司，力扣 希望在 IPO 之前开展一些项目以增加其资本。 由于资源有限，它只能在 IPO 之前完成最多 k 个不同的项目。帮助 力扣 设计完成最多 k 个不同项目后得到最大总资本的方式。

给定若干个项目。对于每个项目 i，它都有一个纯利润 Pi，并且需要最小的资本 Ci 来启动相应的项目。最初，你有 W 资本。当你完成一个项目时，你将获得纯利润，且利润将被添加到你的总资本中。

总而言之，从给定项目中选择最多 k 个不同项目的列表，以最大化最终资本，并输出最终可获得的最多资本。

示例 1:

输入: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

输出: 4

解释:
由于你的初始资本为 0，你尽可以从 0 号项目开始。
在完成后，你将获得 1 的利润，你的总资本将变为 1。
此时你可以选择开始 1 号或 2 号项目。
由于你最多可以选择两个项目，所以你需要完成 2 号项目以获得最大的资本。
因此，输出最后最大化的资本，为 0 + 1 + 3 = 4。


/*
一种贪心的方法。每次找到满足最低profit的最大值就可以。
具体实现方法：
1，设计新的pair，并对其进行排序（按照captital逆序）
2，设计优先队列，把满足captital的变量添加进去
3，弹出pro最大的变量。更新W值。
*/
struct cmp_cap{//排序，使得cap小的在后面
    bool operator()(vector<int> a, vector<int> b){
        return a[1] > b[1];
    }
};
struct cmp_pro{ //排序，使得pro大的在前面
    bool operator()(vector<int> a, vector<int> b){
        return a[0] <= b[0];
    }
};
int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    if(k <= 0) return 0;
    vector<vector<int>> base;
    //第一步，获取排序
    for(int i = 0; i < Profits.size(); i++){
        base.push_back({Profits[i], Capital[i]});
    }
    sort(base.begin(),base.end(),cmp_cap());
    priority_queue<vector<int>,vector<vector<int>>,cmp_pro> que;
    while(k > 0){
        //把所有小于w的全都弹出来,加到优先队列中去
        while(base.size() != 0 && base.back()[1] <= W){
            que.push(base.back());
            base.pop_back();
        }
        if(que.size() == 0) //不再满足条件
            break;
        vector<int> t = que.top();
        que.pop();
        W += t[0];
        k--;
    }
    return W;
}