// POJ 2229 Sumsets
/*
	思路：
	n 为奇数：可以由前一个偶数 +1 而得
	
	n 为偶数，可分为有 1 与无 1
	有 1 可以由前一个奇数 +1 而得 
	无 1 可以由 n/2 乘 2 而得 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define ll long long 

const ll MOD = 1e9;
const int maxn = 1e6+10;

int n;
ll dp[maxn];

int main() {
	cin >> n;
	dp[1] = 1; dp[2] = 2;
	for(int i = 3; i <= n; i++) {
		if(i & 1) dp[i] = dp[i-1];
		else dp[i] = (dp[i-1] + dp[i/2]) % MOD;
	}
	cout << dp[n] << endl;
	
	return 0;
}
