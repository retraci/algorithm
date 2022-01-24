// 最长上升子序列2 
/*
	思路转化
	dp[i] 表示 长度为 i 的序列结尾的字符的最小值 
	利用 dp 数组的递增，用 lower_bound 函数找出插入位置 
	
	初始化 INF
	寻找插入即可 
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1010;
const int INF = 0x3f3f3f3f;

int n, a[maxn];
int dp[maxn];

void solve() {
	memset(dp,INF,sizeof(dp));
	
	for(int i=0;i<n;i++) {
		*lower_bound(dp,dp+n,a[i]) = a[i];
	}
	
	cout << lower_bound(dp,dp+n,INF) - dp << endl;
}

int main() {
	while(cin >> n) {
		for(int i=0;i<n;i++) {
			scanf("%d", &a[i]);
		}
		
		solve();
	}
	
	return 0;
}
