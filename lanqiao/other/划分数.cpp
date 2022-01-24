// 划分数 
/*
	n 个苹果放在 m 个盘子上面
	
	dp[i][j] 表示有 j 个苹果，放在 i 个盘子上的总方案数 
	
	两种情况： 
	1. 每个盘子都有苹果：先在每个盘子上面放一个，剩下 n-m 个苹果直接用 dp[i][j] = dp[i][j-i] 
	2. 必然有空碟子(1,2,...,i)：直接继承 dp[i][j] = dp[i-1][j] 
*/ 

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1010;
const int maxm = 1010;

int n, m, mod;
int dp[maxn][maxm];

void solve() {
	memset(dp,0,sizeof(dp));
	
	// 初始化，没有苹果时，方案数为 1  
	for(int i=0;i<=m;i++) dp[i][0] = 1;
	
	// 份数为主要递推 
	for(int i=1;i<=m;i++) {
		for(int j=0;j<=n;j++) {
			if(j-i >= 0)
				// 不空碟子 + 空碟子 两种情况 
				dp[i][j] = (dp[i][j-i] + dp[i-1][j]) % mod;
			else 
				// i-1 即为 空一个碟子，由于递推的关系，当 i > 2 时，表示的为空 k 个碟子 
				dp[i][j] = (dp[i-1][j]) % mod;
		}
	}
	
	cout << dp[m][n] << endl;
}

int main() {
	while(cin >> n >> m >> mod) {
		solve();
	}
	
	return 0;
}
