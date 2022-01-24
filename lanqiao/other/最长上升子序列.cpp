// 最长上升子序列 
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1010;

int n, a[maxn];
int dp[maxn];

void solve() {
	for(int i=0;i<n;i++) dp[i] = 1;
	
	for(int i=0;i<n;i++) {
		for(int j=0;j<i;j++) {
			if(a[i] > a[j] && dp[j]+1 > dp[i]) dp[i] = dp[j]+1;
		}
	}
	
	cout << dp[n-1] << endl;
}

int main() {
	while(cin >> n) {
		for(int i=0;i<n;i++) {
			scanf("%d", &a[i]);
		}
		
		solve();
	}
	
	return 0;
}

