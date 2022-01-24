// 蓝桥杯9B 测试次数
/*
	思路：
	dp，n 个蛋 m 层楼
	dp[i][j] 表示 i 个手机，需要测试 j 层楼，dp[i][j] 表示最少次数 

	node:
	遍历从所有可能楼层进行摔下，取最多次数(最坏情况)，
	dp[i][j] 维护最小次数 
*/

#include <bits/stdc++.h>

using namespace std;

int n, m;
int dp[4][1010];

int main() {
	n = 3, m = 1000;
	for(int i = 1; i <= 3; i++)
	for(int j = 1; j <= 1000; j++) 
		dp[i][j] = j;
		
	for(int i = 2; i <= 3; i++) {
		for(int j = 1; j <= 1000; j++) {
			// 从 k 楼摔下 
			for(int k = 1; k <= j; k++) {
				dp[i][j] = min(dp[i][j], max(dp[i][j-k], dp[i-1][k-1])+1);
			}
		}
	}
	cout << dp[3][1000] << endl;

	return 0;
}
