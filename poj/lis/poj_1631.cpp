// POJ 1631 Bridging signals
/*
	思路：
	LIS
	
	node:
	1. 如果 a[i] > dp[len-1]  				dp[len++] = a[i]
		即可以增长序列 
	2. 如果 a[i] < dp[j](0 >= j <= len-2) 	dp[j] = a[i] 
		即可以将之前序列的最后元素变小
	lower_bound() 可以寻找 idx 前面都是比 idx 小的  满足*idx >= key 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 4e4+10;

int n;
int a[maxn];
int dp[maxn];

void solve() {
	memset(dp, INF, sizeof(dp));

	for(int i = 0; i < n; i++) {
		*lower_bound(dp, dp+n, a[i]) = a[i];
	}
//	cout << "ans:";
	cout << (lower_bound(dp, dp+n, INF) - dp) << endl;
}

int main() {
	int t;
	cin >> t;

	while(t--) {
		scanf("%d", &n);

		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		solve();
	}

	return 0;
}
