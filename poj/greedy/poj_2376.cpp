// POJ 2376 Cleaning Shifts
/*
	贪心
	
	区间枚举时，不要用 for 循环，会自动 +1 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef pair<int, int> P;

const int maxn = 3e5;

int n, T;
P cow[maxn];
int ls, lt;
int ans = 0;

bool cmp(P p1, P p2) {
	if(p1.first == p2.first) {
		return p1.second > p2.second;
	} else {
		return p1.first < p2.first;
	}
}

void solve() {
	sort(cow, cow+n, cmp);
	lt = cow[0].second;
	ans = 1;
	int i = 0, t = lt+1;

	if(cow[0].first != 1) {
		cout << -1 << endl;
		return;
	}
	while(true) {
		int flag = 0;
		// 看下一个是否符合要求 
		while(i+1<n && cow[i+1].first <= t) {
			i++;
//			printf("%d %d\n", lt, cow[i].second);
			if(lt < cow[i].second) {
				lt = cow[i].second;
				flag = 1;
			}
		}

		if(flag) {
			ans++;
			// 维护下一轮的取值范围 
			t = lt+1;
		} else {
//			cout << i << endl;
			if(lt < T) ans = -1;
			break;
		}
	}

	cout << ans << endl;
}

int main() {
	scanf("%d%d", &n, &T);
	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		cow[i] = P(a, b);
	}
	solve();

	return 0;
}
