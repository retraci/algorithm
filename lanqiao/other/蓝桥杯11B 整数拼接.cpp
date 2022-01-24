// 蓝桥杯11B 整数拼接 
/*
	思路：
	mod 运算
	
	避免相同，而且顺序相反当不同方案
	正着推一遍，逆着推一遍可解决 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;

int n, k;
ll a[maxn];
ll cnt[10][maxn];

int get_len(int x) {
	int res = 0;
	while(x) {
		res++;
		x /= 10;
	}
	return res;
}

void solve() {
	int ans = 0;
	
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < n; i++) {
		int temp = get_len(a[i]);
		int b = (k-(a[i]%k)) % k;
		ans += cnt[temp][b];
		
		ll rate = 10;
		for(int j = 1; j <= 9; j++) {
			cnt[j][(rate*a[i])%k]++;
			rate *= 10;
		}
	}
	
	memset(cnt, 0, sizeof(cnt));
	for(int i = n-1; i >= 1; i--) {
		int temp = get_len(a[i]);
		int b = (k-(a[i]%k)) % k;
		ans += cnt[temp][b];
		
		ll rate = 10;
		for(int j = 1; j <= 9; j++) {
			cnt[j][(rate*a[i])%k]++;
			rate *= 10;
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> k;
	for(int i = 0; i < n; i++) {
		scanf("%I64d", &a[i]);
	}
	
	solve();
	
	return 0;
}
