// POJ 2393 Yogurt factory
/*
	思路：
	成本：提前生产 / 现在生产
	提前生产 = 上一周的成本 + S 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

#define LL long long

using namespace std;

const int maxn = 1e4+10;

int n, S;
int y[maxn], c[maxn], tc[maxn];

void solve() {
	int last = c[0];
	
	LL ans = c[0] * y[0];
	for(int i = 1; i < n; i++) {
		last += S;
		last = min(last, c[i]);
		ans += last * y[i];
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> S;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &c[i], &y[i]);
	}
	solve();
	
	return 0;
}
