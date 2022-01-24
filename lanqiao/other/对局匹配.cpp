// 蓝桥杯 对局匹配
/*
	思路：
	贪心 
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;

int n, k, mx;
int cnt[MAXN];

void solve() {
	long long ans = 0;
	for(int i = 0; i+k <= mx; i++) {
		if(cnt[i] == 0) continue;

		if(k > 0) {
			int temp = min(cnt[i], cnt[i+k]);
			cnt[i] -= temp;
			cnt[i+k] -= temp;
			ans += temp;
		} else {
			if(cnt[i] < 2) continue;
			ans += cnt[i]/2;
			cnt[i] &= 1;
		}
	}
	cout << n-ans << endl;
}

int main() {
	cin >> n >> k;
	memset(cnt, 0, sizeof(cnt));
	mx = 0;

	int a;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a);
		cnt[a]++;
		mx = max(mx, a);
	}
	solve();

	return 0;
}
