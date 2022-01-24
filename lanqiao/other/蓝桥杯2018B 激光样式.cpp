// 蓝桥杯2018B 激光样式 
/*
	思路：
	枚举 
*/

#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

bool check(int x) {
	int last = 0;
	while(x) {
		int temp = x & 1;
		if(temp && last) return false;
		last = temp;
		x >>= 1;
	}
	return true;
}

int main() {
	int n = 30;
	int ans = 0;
//	for(int i = 0; i < (1<<n); i++) {
//		if(check(i)) ans++;
//	}
//	cout << ans << endl;
	
	int dp[35][2] = {0};
	dp[1][1] = dp[1][0] = 1;
	for(int i = 2; i <= 30; i++) {
		dp[i][0] = dp[i-1][0] + dp[i-1][1];
		dp[i][1] = dp[i-1][0];
	}
	cout << dp[30][0]+dp[30][1] << endl;
	
	return 0;
} 
