// 蓝桥杯10B 等差数列
/*
	思路：
	gcd 
*/

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> nums, delta;

int gcd(int a, int b) {
	if(a < b) swap(a, b);
	return b==0? a : gcd(b, a%b);
}

void solve() {
	sort(nums.begin(), nums.end());
	
	for(int i = 1; i < n; i++) {
		delta.push_back(nums[i]-nums[i-1]);
	}
	
	int d = gcd(delta[0], delta[1]);
	for(int i = 2; i < n-1; i++) {
		if(d == 1) break;
		d = gcd(d, delta[i]);
	}
	
	int ans = (nums[n-1] - nums[0]) / d + 1;
	
	cout << ans << endl;
}

int main() {
	cin >> n;
	int temp;
	for(int i = 0; i < n; i++) {
		scanf("%d", &temp);
		nums.push_back(temp);
	}
	solve();
	
	return 0;
}

