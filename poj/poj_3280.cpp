// POJ 3280 Cheapest Palindrome
/*
	思路：
	dp[i][j] 表示 区间 [i, j] 的最小代价
	
	1. 如果边界相同，则直接传递 
	dp[i][j] = dp[i+1][j-1]
	2. 如果边界不同，则需要进行处理（添加或删除
	dp[i][j] = min(dp[i+1][j] + p[str[i]], dp[i][j-1] + p[str[j]]) 
	
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

typedef pair<int, int> P;

const int INF = 0x3f3f3f3f;
const int maxn = 30;
const int maxm = 2010;

string str;
int n, m;
int dp[maxm][maxm];
P alp[maxn];

void solve() {
	int len = str.length();
	for(int k = 1; k < len; k++) {
		for(int i = 0,j = k; j < len; i++,j++) {
			if(str[i] == str[j]) {
				dp[i][j] = dp[i+1][j-1];
			} else {
				int pi = min(alp[str[i]-'a'].first, alp[str[i]-'a'].second);
				int pj = min(alp[str[j]-'a'].first, alp[str[j]-'a'].second);
				
				dp[i][j] = min(dp[i][j-1]+pj, dp[i+1][j]+pi);
			}
		}
	}
	cout << dp[0][len-1] << endl;
}

int main() {
	cin >> n >> m >> str;
	char a;
	int b, c;
	for(int i = 0; i < n; i++) {
		cin >> a;
		scanf("%d%d", &b, &c);
		alp[a-'a'].first = b;
		alp[a-'a'].second = c;
	}
	solve();

	return 0;
}
