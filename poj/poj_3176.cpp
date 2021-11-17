// POJ 3176 Cow Bowling
/*
	思路：
	dp，倒着推，从最后一行开始 dp[i][j] = nums[i][j] + max(dp[i+1][j], dp[i+1][j+1]) 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 400;

int n, nums[maxn][maxn], dp[maxn][maxn];

void solve() {
	for(int j = 0; j < n; j++) {
		dp[n-1][j] = nums[n-1][j];
	}
	
	for(int i = n-2; i >= 0; i--) {
		for(int j = 0; j <= i; j++) {
			if(j+1 <= i+1)
				dp[i][j] = nums[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
			else
				dp[i][j] = nums[i][j] + dp[i+1][j];
		}
	}
	cout << dp[0][0] << endl;
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++) {
			scanf("%d", &nums[i][j]);
		}
	}
	solve();
	
	return 0;
}
