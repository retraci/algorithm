// 阶乘之和
/*

*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll MOD = 1e9;

ll n, m;
ll ans;

int main() {
	cin >> n >> m;
	
	ll cur = 1;
	for (int i = 1; i <= n; i++) {
		cur *= i;
		cur %= m;
		ans += cur;
		ans %= m;
	}
	cout << ans << endl;
	
	return 0;
}
