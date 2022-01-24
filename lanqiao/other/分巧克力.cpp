// 蓝桥杯 分巧克力
/*
	思路：
	二分答案 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 100010;

int n, k;
int x[maxn], y[maxn];

int cal(int len) {
	int res = 0;
	for(int i = 0; i < n; i++) {
		int a = x[i] / len;
		int b = y[i] / len;
		res += a*b;
	}
	return res;
}

void solve() {
	int l = 0, r = INF;
	
	int ans = 0;
	while(l <= r) {
		int mid = (l+r)/2;
		int a = cal(mid);
		if(a >= k) {
			l = mid+1;
			ans = max(ans, mid);
		} else if(a < k) {
			r = mid-1;
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> k;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &x[i], &y[i]);
	}
	solve();
	
	return 0;
} 
