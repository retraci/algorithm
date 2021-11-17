// POJ 2392 Space Elevator
/*
	思路：
	多重背包 
	由于价值与容量一样，用 dp 数组记录能否组成该容量即可 
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 410;
const int maxm = 40010;

struct Node {
	int h, a, c;
};

int n, m;
Node ns[maxn];
int dp[maxm];

bool cmp(Node n1, Node n2) {
	return n1.a < n2.a;
}

void solve() {
	int cnt[maxm];
	memset(dp, 0, sizeof(dp));
	sort(ns, ns+n, cmp);
	
	int ans = 0;
	dp[0] = 1;
	for(int i = 0; i < n; i++) {
		int tm = ns[i].a;
		memset(cnt, 0, sizeof(cnt));
		for(int j = ns[i].h; j <= tm; j++) {
			if(cnt[j-ns[i].h] >= ns[i].c || dp[j]) continue;
			if(dp[j-ns[i].h]) {
				cnt[j] = cnt[j-ns[i].h] + 1;
				dp[j] = 1;
				ans = max(ans, j);
			}
		}
	}

	cout << ans << endl;
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d%d%d", &ns[i].h, &ns[i].a, &ns[i].c);
		m = max(m, ns[i].a);
	}
	solve();
	
	return 0;
}
