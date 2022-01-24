// 蓝桥杯2019B B 
/*
	思路：
	埃筛 + 01背包 
*/

#include <bits/stdc++.h>

#define ll long long

using namespace std;

int isn_prime[2019];
vector<ll> ps;

int main() {
	isn_prime[1] = 1;
	for(int i = 2; i <= 2019; i++) {
		if(isn_prime[i]) continue;
		ps.push_back(i);
 		for(int k = 2; k*i <= 2019; k++) {
			isn_prime[i*k] = 1;
		}
	}
//	for(int i = 1; i <= 100; i++) {
//		if(!isn_prime[i]) cout << i << endl;
//	}
	int n = 2019;
	vector<vector<ll> > dp(ps.size()+1, vector<ll>(2020, 0));
	for(int i = 0; i <= ps.size(); i++) dp[i][0] = 1;
	
	// 枚举素数 
	for(int i = 1; i <= ps.size(); i++) {
		// 枚举数字 
		for(int j = 0; j <= n; j++) {
			// 不选的方案数 
			dp[i][j] = dp[i-1][j];
			if(j-ps[i-1] >= 0) {
				// 选的方案数 
				dp[i][j] += dp[i-1][j-ps[i-1]];
			}
		}
	}
	cout << dp[ps.size()][n] << endl;
	
	return 0;
} 
