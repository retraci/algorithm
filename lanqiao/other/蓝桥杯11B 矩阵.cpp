// 蓝桥杯11B 矩阵
/*
	思路：
	dp
	dp[i][j] 表示 i 个数，第一行有 j 个数的方案数 
*/

#include <bits/stdc++.h>

using namespace std;

int n = 2020;
int mod = 2020;
int dp[3000][3000];

int main() {
	
	dp[1][1] = 1;
	// 填第 i 个数时候
	for(int i = 1; i <= 2020; i++) {
		for(int j = 1; j <= i; j++) {
			dp[i][j] += dp[i-1][j-1];	// 填入第一行 
			if(i-j <= j) {
				dp[i][j] += dp[i-1][j];	// 填入第二行 
			}
			dp[i][j] %= 2020;
		}
	}
	
	cout << dp[2020][1010] << endl;

	return 0;
}
