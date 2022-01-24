// 蓝桥杯2015B 五星填数 
/*
	思路：
	全排列 
*/

#include <bits/stdc++.h>

using namespace std;

int nums[10] = {1,2,3,4,5,6,8,9,10,12};
int ans;

void dfs(int x) {
	if(x == 10) {
		int a = nums[1]+nums[2]+nums[3]+nums[4];
		int b = nums[0]+nums[2]+nums[5]+nums[8];
		int c = nums[0]+nums[3]+nums[6]+nums[9];
		int d = nums[1]+nums[5]+nums[7]+nums[9];
		int e = nums[4]+nums[6]+nums[7]+nums[8];
		
		if(a==b && a==c && a==d && a==e) ans++;
	}
	
	for(int i = x; i < 10; i++) {
		swap(nums[x], nums[i]);
		dfs(x+1);
		swap(nums[x], nums[i]);
	}
}

int main() {
	dfs(0);
	cout << ans/10 << endl;
	
	return 0;
}
