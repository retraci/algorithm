// 有趣的数 - 201312-4
/*
	思路：
	i 位置能放什么数，取决于前面放过什么数
	以前面放过什么数作为 状态，进行状态转移	
	
	易得 首位为 2
	由于条件限制，可往后推的情况只有 6 种
	因为前面用过与否，才会影响后面的选择，所以以用过什么数字作为状态，进行递推 
	
	0 : 只用过 2 		dp[i][0] = dp[i-1][0]
	1 : 只用过 2 0		dp[i][1] = dp[i-1][0] + dp[i-1][1] * 2
	2 : 只用过 2 3 		dp[i][2] = dp[i-1][0] + dp[i-1][2]
	3 : 只用过 2 0 1 	dp[i][3] = dp[i-1][1] + dp[i-1][3] * 2
	4 : 只用过 2 0 3 	dp[i][4] = dp[i-1][1] + dp[i-1][2] + dp[i-1][4] * 2
	5 : 只用过 2 0 3 1	dp[i][5] = dp[i-1][3] + dp[i-1][4] + dp[5] * 2 
*/

#include <cstdio>

#define ll long long 

using namespace std;

const ll MOD = 1000000007;
const int maxn = 1010;

int n;
ll dp[maxn][6];

int main() {
	scanf("%d", &n);
	dp[1][0] = 1;
	for(int i = 2; i <= n; i++) {
		dp[i][0] = dp[i-1][0] % MOD;
        dp[i][1] = (dp[i-1][0] + dp[i-1][1] * 2) % MOD;
        dp[i][2] = (dp[i-1][0] + dp[i-1][2] * 1) % MOD;
        dp[i][3] = (dp[i-1][1] + dp[i-1][3] * 2) % MOD;
        dp[i][4] = (dp[i-1][1] + dp[i-1][2] + dp[i-1][4] * 2) % MOD;
        dp[i][5] = (dp[i-1][3] + dp[i-1][4] + dp[i-1][5] * 2) % MOD;
	}
	printf("%lld\n", dp[n][5]);
	
	return 0;
}
