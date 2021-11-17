// POJ 3046 Ant Counting
/*
	思路：
	多重背包
*/

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const long long MOD = 1000000;

long long T, A, S, B;
long long dp[1005][100005];
long long num[1005];

void solve() {
	// 初始化 
	for(int i = 0; i <= T; i++) dp[i][0] = 1;
	
	for(int i = 0; i < T; i++)
		for(int j = 1; j <= B; j++) {
			if(j-1-num[i] >= 0)
				dp[i+1][j] = (dp[i+1][j-1]+dp[i][j]-dp[i][j-1-num[i]]+MOD) % MOD;
			else
				dp[i+1][j] = (dp[i+1][j-1]+dp[i][j]) % MOD;
		}
	long long ans = 0;
	for(int j = S; j <= B; j++) ans = (ans + dp[T][j]) % MOD;

	printf("%lld\n",ans);
}

int main() {
	while(~scanf("%lld%lld%lld%lld", &T, &A, &S, &B)) {
		memset(num,0,sizeof(num));
		int x;
		for(int i = 0; i < A; i++) {
			scanf("%lld", &x);
			num[x-1]++;
		}
		
		solve();
	}

	return 0;
}
