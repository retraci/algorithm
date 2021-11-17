// POJ 3045 Cow Acrobats
/*

*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define ll long long

struct node {
	ll w;
	ll s;
};

const int INF = 0x3f3f3f3f;
const int maxn = 50010;

int n;
node cs[maxn];

bool cmp(node a, node b) {
	return a.s+a.w < b.s+b.w;
}

void solve() {
	sort(cs, cs+n, cmp);
	ll sum = 0, ans = -INF;
	for(int i = 0; i < n; i++) {
		ans = max(ans, sum-cs[i].s);
		sum += cs[i].w;
	}
	
	cout << ans << endl;
}

int main() {
	while(cin >> n) {
		for(int i = 0; i < n; i++) {
			scanf("%I64d%I64d", &cs[i].w, &cs[i].s);
		}
		solve();

	}
	
	return 0;
}
