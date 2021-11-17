// POJ 2385 Apple Catching
/*
	思路：
	dp[i][j] i表示时间，j表示使用了多次变换 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1010;
const int maxw = 40;

int t, w;
int dp[maxn][maxw];
int ap[maxn];

int main() {
	cin >> t >> w;
	for(int i = 1; i <= t; i++) scanf("%d", &ap[i]);

	for(int i = 1; i <= t; i++) {
		// 不换 
		for(int j = 0; j <= w; j++) {
			int temp = dp[i-1][j];
			if(((j+1) & 1) && ap[i] == 1) temp++;
			if(!((j+1) & 1) && ap[i] == 2) temp++;
			dp[i][j] = temp;
		}
		// 换 
		for(int j = 1; j <= w; j++) {
			int temp = dp[i-1][j-1];
			if(((j+1) & 1) && ap[i] == 1) temp++;
			if(!((j+1) & 1) && ap[i] == 2) temp++;
			dp[i][j] = max(dp[i][j], temp);
		}
	}
	int ans = 0;
	for(int j = 0; j <= w; j++) {
		ans = max(ans, dp[t][j]);
	}
	cout << ans << endl;
	
	return 0;
}
