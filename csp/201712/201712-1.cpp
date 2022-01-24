// 201712-1 最小差值
/*
	思路：
	排序 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

int n;
int nums[maxn];

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	
	sort(nums, nums+n);
	
	int ans = 0x3f3f3f3f;
	for(int i = 1; i < n; i++) {
		int temp = abs(nums[i]-nums[i-1]);
		ans = min(ans, temp);
	}
	cout << ans << endl;
	
	return 0;
}
