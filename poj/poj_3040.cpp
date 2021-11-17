// POJ 3040 Allowance
/*
	思路：贪心
	枚举方案：
	1. 先用大的面额尽量凑大，但不能超过 c
	2. 再用小的面额凑够 c
	3. 该方案的可供数目 = min(num[i] / used[i]) 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> P;

const int INF = 0x3f3f3f3f;
const int maxn = 25;

vector<P> coin;
int n, c;
int used[maxn];

void solve() {
	int ans = 0;
	sort(coin.begin(), coin.end());

	for(int i = n-1; i >= 0; i--) {
		if(coin[i].first < c) break;

		ans += coin[i].second;
		n--;
	}
	
	// 枚举方案 
	while(1) {
		int cost = c;
		int flag = 0;
		memset(used, 0, sizeof(used));

		for(int i = n-1; i >= 0; i--) {
			if(coin[i].second) {
				used[i] = min(coin[i].second, cost/coin[i].first);
				cost -= used[i]*coin[i].first;
				if(cost == 0) {
					flag = 1;
					break;
				}
			}
		}
		if(cost > 0) {
			for(int i = 0; i < n; i++) {
				while(coin[i].second > used[i]) {
					cost -= coin[i].first;
					used[i]++;
					if(cost <= 0) {
						flag = 1;
						break;
					}
				}
				if(flag) break;
			}
		}
		if(!flag) break;
		
		int temp = INF;
		for(int i = 0; i < n; i++) {
			if(used[i]) temp = min(temp, coin[i].second/used[i]);
		}
		ans += temp;
		for(int i = 0; i < n; i++) {
			if(used[i]) coin[i].second -= used[i]*temp;
		}
	}

	cout << ans << endl;
}

int main() {
	cin >> n >> c;
	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		coin.push_back(P(a, b));
	}
	solve();

	return 0;
}
