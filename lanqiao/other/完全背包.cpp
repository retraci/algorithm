// 完全背包 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 110;
const int maxw = 1e5+10;

int n, W;
int v[maxn], w[maxn];
int dp[2][maxn];

void solve() {
	memset(dp,0,sizeof(dp));
	
	for(int i=0;i<n;i++) {
		for(int j=0;j<=W;j++) {
			if(j >= w[i+1])
				dp[i+1 & 1][j] = max(dp[i & 1][j],dp[i+1 & 1][j-w[i+1]]+v[i+1]);
			else 
				dp[i+1 & 1][j] = dp[i & 1][j];
		}
	}
	
	cout << dp[n & 1][W];
}

int main() {
	while(cin >> n >> W) {
		for(int i=1;i<=n;i++) {
			scanf("%d%d", &w[i], &v[i]);
		}
		
		solve();
	}
		
	return 0;
}
