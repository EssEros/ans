#include <iostream>
#include <vector>
using namespace std;


void getDP(vector<int> &weight, vector<int> &value, vector<vector<vector<int>>> &dp, int &bagSize1, int &bagSize2){
    int cnt = weight.size();
    dp.resize(cnt+1);
    for(int i = 0; i <= cnt; ++i){
        dp[i].resize(bagSize1+1);
        for(int j = 0; j <= bagSize1; ++j)
            dp[i][j].resize(bagSize2+1);
    }
    for(int i = 1; i <= cnt; ++i)
        for(int j = 1; j <= bagSize1; ++j)
            if(j < weight[i-1])
                dp[i][j][0] = dp[i-1][j][0];
            else
                dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j-weight[i-1]][0] + value[i-1]);

    for(int i = 1; i <= cnt; ++i)
        for(int j = 1; j <= bagSize2; ++j)
            if(j < weight[i-1])
                dp[i][0][j] = dp[i-1][0][j];
            else
                dp[i][0][j] = max(dp[i-1][0][j], dp[i-1][0][j-weight[i-1]] + value[i-1]);
                                                            
    for(int i = 1; i <= cnt; ++i){
        for(int j = 1; j <= bagSize1; ++j){
            for(int k = 1; k <= bagSize2; ++k){
                // 两个背包都放不下时
                if(j < weight[i-1] && k < weight[i-1])
                    dp[i][j][k] = dp[i-1][j][k];
                // 背包 2 放不下，就放背包 1
                else if (j >= weight[i-1] && k < weight[i-1])
                    dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j-weight[i-1]][k] + value[i-1]);
                // 背包 1 放不下，就放背包 2
                else if (j < weight[i-1] && k >= weight[i-1])
                    dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j][k-weight[i-1]] + value[i-1]);
                else {
                    int tmpK = max(1, k-weight[i-1]);
                    int tmpJ = max(1, j-weight[i-1]);
                    dp[i][j][k] = max(dp[i-1][j][k], max(dp[i-1][j][tmpK], dp[i-1][tmpJ][k]) + value[i-1]);
                }
            }
        }
    }
}
void getAns(vector<int> &weight, vector<int> &value, vector<vector<vector<int>>> &dp, vector<int> &ans, int &bagSize1, int &bagSize2){
    int cnt = weight.size();
    ans.resize(cnt, 0);
    int b1 = bagSize1, b2 = bagSize2;
    for(int k = cnt; k > 0; --k){
        if(dp[k][b1][b2] == dp[k-1][b1][b2])
            ans[k-1] = 0;
        else {
            if(b1 < weight[k-1] && b2 >= weight[k-1]){
                ans[k-1] = 2;
                b2 -= weight[k-1];
            }
            else if(b1 >= weight[k-1] && b2 < weight[k-1]){
                ans[k-1] = 1;
                b1 -= weight[k-1];
            }
            else if(b1 >= weight[k-1] && b2 >= weight[k-1]){
                if(dp[k-1][b1-weight[k-1]][b2] > dp[k-1][b1][b2-weight[k-1]]){
                    ans[k-1] = 1;
                    b1 -= weight[k-1];
                } else {
                    ans[k-1] = 2;
                    b2 -= weight[k-1];
                }
            }    
        }
    }
}


int main(){
    vector<int> weight = {18, 9, 23, 20, 59, 61, 70, 75, 76, 30}, value = {78, 35, 89, 36, 94, 75, 74, 79, 80, 16};          // 这里直接填入数据
    int bagSize1 = 203, bagSize2 = 156; // 这里修改背包容量
    int cnt = weight.size();
    vector<vector<vector<int>>> dp;
    vector<int> ans;
    getDP(weight, value, dp, bagSize1, bagSize2);
    getAns(weight, value, dp, ans, bagSize1, bagSize2);
    cout << dp[cnt][bagSize1][bagSize2] << endl;
    for(auto &i : ans)
        cout << i << " ";
    cout << endl;
    return 0;
}
