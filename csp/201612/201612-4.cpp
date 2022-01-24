// 201612-4 压缩编码
/*
	思路：
	区间 dp 
	取石子问题 2 
	合并石子，有相对位置的哈夫曼树 
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 1010;

int n;
int a[maxn], prefix[maxn];
int dp[maxn][maxn];

int main() {
	cin >> n;
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		prefix[i] = prefix[i-1] + a[i];
	}
	memset(dp, INF, sizeof(dp));
	
	for(int i = 0; i <= n; i++) dp[i][i] = 0;
	
	// 石子个数 len+1 
	for(int len = 1; len <= n-1; len++) {
		for(int i = 1; i+len <= n; i++) {
			for(int k = i; k <= i+len; k++) {
				dp[i][i+len] = min(dp[i][i+len], dp[i][k]+dp[k+1][i+len]+prefix[i+len]-prefix[i-1]);
			}
		}
	}
	cout << dp[1][n] << endl;
	
	return 0;
}
