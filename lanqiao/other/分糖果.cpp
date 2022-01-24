// 蓝桥杯 分糖果
/*
	思路：
	模拟 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100;

int n;
int nums[maxn], nex[maxn];

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}
	
	int flag = 1;
	int ans = 0;
	while(flag) {
		flag = 0;
		for(int i = 0; i < n; i++) {
			if(i == n-1) {
				nex[0] = nums[i]/2;
			} else {
				nex[i+1] = nums[i]/2;
			}
			nums[i] /= 2;
		}
		for(int i = 0; i < n; i++) {
			nums[i] += nex[i];
			if(nums[i]&1) {
				nums[i]++;	
				ans++;
			}
		}
		for(int i = 0; i < n-1; i++) {
			if(nums[i] != nums[i+1]) flag = 1;
		}
		
	}
	
	cout << ans << endl;
	
	return 0;
} 
