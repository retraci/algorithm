// 饮料换购
/*

*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, m;

int main() {
	cin >> n >> m;
	
	ll ans = n/m;
	ll cur = n/m;
	ll cnt1 = cur, cnt2 = cur;
	while (cnt1 >= 2 || cnt2 >= 4) {
		cur = cnt1/2 + cnt2/4;
		ans += cur;
		cnt1 = (cnt1&1) + cur;
		cnt2 = (cnt2%4) + cur;
	}
	cout << ans << endl;
	
	return 0;
}
