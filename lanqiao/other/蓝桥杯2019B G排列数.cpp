// 蓝桥杯2019B G排列数
/*
	思路：
	全排列 dfs + 剪枝
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD = 123456;

int n, m;
int ans;
vector<int> a;

void dfs(int x) {
	int t = 0;
	int temp = 0;
	for(int i = 1; i+1 < n; i++) {
		if((a[i]>a[i-1] && a[i]>a[i+1]) || (a[i]<a[i-1] && a[i]<a[i+1])) t++;
		if(i == x-1) temp = t;
	}
	if(x >= n) {
		if(t+1 == m) {
			ans++;
		}
		return;
	}
	if(temp+1 > m) return;

	for(int i = x; i < n; i++) {
		swap(a[x], a[i]);
		dfs(x+1);
		swap(a[x], a[i]);
	}
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < n; i++) a.push_back(i+1);
	dfs(0);
	cout << ans%MOD << endl;

	return 0;
}
