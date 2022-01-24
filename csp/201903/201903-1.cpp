// 201903-1
/*
	思路；
	枚举 
*/

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> nums;

int main() {
	cin >> n;
	if(n == 0) {
		printf("0 0 0\n");
		return 0;
	}
	nums.resize(n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	
	int mx = nums[0];
	int mn = nums[0];
	double midium;
	if(n & 1) {
		midium = nums[n/2];
	} else {
		midium = 1.0*(nums[(n-1)/2] + nums[(n-1)/2+1]) / 2;
	}
	for(int i = 1; i < n; i++) {
		mx = max(mx, nums[i]);
		mn = min(mn, nums[i]);
	}
	if(midium - floor(midium) > 0) {
		printf("%d %.1llf %d\n", mx, midium, mn);
	} else {
		printf("%d %.0llf %d\n", mx, midium, mn);
	}
	
	return 0;
}
