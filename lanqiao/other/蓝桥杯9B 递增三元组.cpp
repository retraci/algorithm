// 蓝桥杯9B 递增三元组
/*
	思路：
	遍历 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;

int n;
int a[maxn], b[maxn], c[maxn];

void solve() {
	int ans = 0;
	sort(a, a+n); sort(b, b+n); sort(c, c+n);
	
	int last = 0, flag;
	for(int i = 0; i < n; i++) {
		flag = 0;
		for(int j = last; j < n; j++) {
			if(b[j] > a[i]) {
				if(!flag) {
					last = j;
					flag = 1;
				}
				// upper_bound 获取 大于 k 的最小值 
				ans += c+n-upper_bound(c, c+n, b[j]);
			}
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n;
	
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < n; i++) scanf("%d", &b[i]);
	for(int i = 0; i < n; i++) scanf("%d", &c[i]);
	
	solve();
	
	return 0;
} 
