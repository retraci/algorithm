// 蓝桥杯 连号区间数 
/*
	思路：
	枚举 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 50010;

int n;
int nums[maxn];

void solve() {
	int ans = n;
	for(int i = 0; i < n; i++) {
		int mx = nums[i], mn = nums[i];
		for(int j = i+1; j < n; j++) {
			int len = j-i;
			mx = max(mx, nums[j]);
			mn = min(mn, nums[j]);
			if(mx - mn == len) ans++;
		}
	}
	cout << ans << endl;
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	solve();
	
	return 0;
}
