// POJ 3185 The Water Bowls
/*
	思路：
	开关问题 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int nums[30];
int flip[30];	// [i, i+2] 进行翻转 

int cal(int first) {
	memset(flip, 0, sizeof(flip));
	int res = 0, sum = 0;
	nums[0] = first;
	
	for(int i = 0; i <= 19; i++) {
		if((nums[i]+sum) & 1) {
			res++;
			flip[i]++;
		}
		// 维护下一状态的翻转次数 
		sum += flip[i];
		if(i-2 >= 0) 
			sum -= flip[i-2];
	}
	
	return res;
}

int main() {
	for(int i = 1; i <= 20; i++) {
		scanf("%d", &nums[i]);
	}
	int ans = min(cal(0), cal(1));
	cout << ans << endl;
	
	return 0;
}
