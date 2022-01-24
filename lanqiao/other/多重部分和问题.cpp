// 多重部分和问题
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 110;
const int maxk = 1e5+10;

int n, k;
int a[maxn], m[maxn];
int dp[maxn][maxk];

void solve() {
	memset(dp,0,sizeof(0));
	
	dp[0][0] = 1;
	for(int i=0;i<n;i++) {
		for(int j=1;j<=k;j++) {
			for(int q=0;q<=m[i] && j-q*a[i]>=0;q++) {
				dp[i+1][j] |= dp[i][j-q*a[i]];
			}
		}
	}
	
	cout << dp[n][k] << endl;
}

int main() {
	while(cin >> n >> k) {
		for(int i=0;i<n;i++) {
			scanf("%d", &a[i]);
		}
		
		for(int i=0;i<n;i++) {
			scanf("%d", &m[i]);
		}
		
		solve();
	}
	
	return 0;
} 
