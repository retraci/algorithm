// 蓝桥杯8B 承压计算 
/*
	思路：
	递推 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 50;

int n;
int weight[maxn][maxn];
double ans[maxn][maxn];

void solve() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++) {
			ans[i][j] = weight[i][j];
		}
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++) {
			ans[i+1][j] += ans[i][j] / 2.0;
			ans[i+1][j+1] += ans[i][j] / 2.0;
		}
	}
	
	cout << endl << endl;
	for(int i = 0; i < n+1; i++) {
		for(int j = 0; j <= i; j++) {
			printf("%.1lf ", ans[i][j]);
		}
		cout << endl;
	}
		
	double mn = ans[n][0], mx = ans[n][0];
	for(int j = 1; j <= n; j++) {
		mn = min(mn, ans[n][j]);
		mx = max(mx, ans[n][j]);
	}
	double rate = 2086458231.0 / mn;
	double res = mx * rate;
	printf("%lf", res);
}

int main() {
	n = 29;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++) {
			scanf("%d", &weight[i][j]);
		}
	}

	
	solve();
	
	return 0;
}
