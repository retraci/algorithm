// POJ 3666 Making the Grade
/*
	思路：
	dp[i][j] 表示第 i 个阶梯以 b[j] 结尾的最小代价
	dp[i][j] = last + abs(a[i]-b[j])
	last 为从 0 到 j 的最小代价 
	递增推一次，递减推一次，取最小值 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 2020;

int n;
int a[maxn], b[maxn];
int dp[2][maxn];

bool cmp(int a, int b) {
	return a > b;
}

void solve() {
	int cnt = unique(b, b+n) - b;
	sort(b, b+cnt);
	
	// 递增 
	for(int j = 0; j < cnt; j++) {
		dp[0][j] = abs(a[0]-b[j]);
	}

	for(int i = 1; i < n; i++) {
		int last = dp[(i-1)%2][0];
		for(int j = 0; j < cnt; j++) {
			last = min(last, dp[(i-1)%2][j]);
			dp[i%2][j] = last + abs(a[i]-b[j]);
		}
	}
	int ans1 = dp[(n-1)%2][0];
	for(int j = 0; j < cnt; j++) {
		ans1 = min(ans1, dp[(n-1)%2][j]);
	}
	
	// 递减 
	memset(dp, 0, sizeof(dp));
	for(int j = 0; j < cnt; j++) {
		dp[0][j] = abs(a[0]-b[j]);
	}

	for(int i = 1; i < n; i++) {
		int last = dp[(i-1)%2][cnt-1];
		for(int j = cnt-1; j >= 0; j--) {
			last = min(last, dp[(i-1)%2][j]);
			dp[i%2][j] = last + abs(a[i]-b[j]);
		}
	}
	int ans2 = dp[(n-1)%2][0];
	for(int j = 0; j < cnt; j++) {
		ans2 = min(ans2, dp[(n-1)%2][j]);
	}
	
	cout << min(ans1, ans2) << endl;
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	solve();

	return 0;
}
