// 超大背包问题
/*
	背包问题 O(n*W)，由于这个 W 过大，dp 无法解决这个问题
	n 比较小，直接折半枚举
	
	思路：
	枚举前半，枚举后半，搜索 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 40;

typedef pair<long long, long long> P;

int n, W, w[maxn], v[maxn];
P ps[1 << (maxn/2)];

void solve() {
	// 枚举前半
	int n2 = n / 2;
	for(int i = 0; i < (1 << n2); i++) {
		long long sw = 0, sv = 0;
		for(int j = 0; j < n2; j++) {
			if(i >> j & 1) {
				sw += w[j];
				sv += v[j];
			}
		}
		ps[i] = P(sw, sv);
	}
	// 筛选情况
	sort(ps, ps+(1 << n2));
	int m = 1;	// 筛选后的 ps 大小
	for(int i = 1; i < (1 << n2); i++) {
		if(ps[i].second > ps[i-1].second)
			ps[m++] = ps[i];
	}
	// 枚举后半
	long long res = 0;
	for(int i = 0; i < (1 << (n - n2)); i++) {
		long long sw = 0, sv = 0;
		for(int j = 0; j < n - n2; j++) {
			if((i >> j) & 1) {
				sw += w[n2 + j];
				sv += v[n2 + j];
			}
		}
		if(sw > W) continue;
		int temp = W - sw;
		long long tv = (lower_bound(ps, ps+m, P(temp, 0)))->second;
		res = max(res, tv + sv);
	}
	cout << res << endl;
}

int main() {
	cin >> n >> W;
	for(int i = 0; i < n; i++) {
		scanf("%d", &w[i]);
	}
	for(int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
	solve();

	return 0;
}
