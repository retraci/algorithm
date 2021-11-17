// POJ 3258 River Hopscotch
/*
	思路：
	二分答案 最小值最大化问题 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxn = 50010;

int l, n, m;
int nums[maxn];

bool check(int x) {
	int rocks = n - m;
	int sum = 0;
	int last = 0;
	
	for(int i = 0; i < n; i++) {
		// 小于最小跳跃距离，移除石子 
		if(nums[i]-last < x) {
			continue;
		} else {
			// 大于等于最小跳跃距离，保留石子 
			sum++; last = nums[i];
			if(l-last <= x) break;
		}
	}
	
	return sum >= rocks;
}

void solve() {
	int low = 0, high = l;
	
	int ans = 0;
	sort(nums, nums+n);
	while(low <= high) {
		int mid = (low+high) >> 1;	// 奶牛的最小跳跃距离 
		if(check(mid)) {
			ans = max(ans, mid);
			low = mid+1;
		} else {
			high = mid-1;
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> l >> n >> m;
	for(int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	solve();
	
	return 0;
}
