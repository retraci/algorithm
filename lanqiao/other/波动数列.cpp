// 蓝桥杯 波动数列 
/*
	思路：
	dfs
	 
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

const ll MOD = 100000007;

ll n, s, a, b, ans;

void dfs(ll x, ll cnt, ll sum) {
	if(cnt == n && sum == s) {
		ans = (ans+1) % MOD;
		return;
	}
	if(cnt == n) return;
	dfs(x+a, cnt+1, sum+x+a);
	dfs(x-b, cnt+1, sum+x-b);
}

void solve() {
	ans = 0;
	ll minn = s-n*a;
	ll maxx = s+n*b;
	for(int i = minn; i <= maxx; i++) {
		dfs(i, 1, i);
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> s >> a >> b;
	solve();
	
	return 0;
}
