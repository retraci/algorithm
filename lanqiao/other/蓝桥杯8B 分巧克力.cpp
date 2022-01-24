// 蓝桥杯8B 分巧克力 
/*
	思路：
	二分答案 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;

int n, k;
int w[maxn], h[maxn];
int mx;

bool check(int x) {
	int cnt = 0;
	
	for(int i = 0; i < n; i++) {
		int cw = w[i] / x;
		int ch = h[i] / x;
		
		cnt += cw * ch;
	}
	
	return cnt >= k;
} 

void solve() {
	int l = 0, r = mx;
	
	int ans = 0;
	while(l <= r) {
		int mid = (l+r) / 2;
		if(check(mid)) {
			ans = max(ans, mid);
			l = mid+1;
		} else {
			r = mid-1;
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> k;
	
	mx = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &w[i], &h[i]);
		if(w[i] > mx) mx = w[i];
		if(h[i] > mx) mx = h[i];
	}
	solve();
	
	return 0;
}
