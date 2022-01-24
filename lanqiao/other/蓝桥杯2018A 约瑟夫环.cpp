// 蓝桥杯2018A 约瑟夫环 
/*
	思路：
	dp 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000010;

int n, k; 
int dp[maxn];

int main() {
	cin >> n >> k;
	dp[1] = 0;
	
	for(int i = 2; i <= maxn; i++) dp[i] = (dp[i-1]+k) % i;
	cout << dp[n] + 1 << endl;
	
	return 0;
}
