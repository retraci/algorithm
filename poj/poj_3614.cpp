// POJ 3614 Sunscreen
/*
	思路：
	贪心 + 优先队列 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> P;

const int maxn = 2510;

int n, m;
P cow[maxn], spf[maxn];

void solve() {
	priority_queue<int, vector<int>, greater<int> > que;
	sort(cow, cow+n);
	sort(spf, spf+m);
	
	int j = 0, ans = 0;
	for(int i = 0; i < m; i++) {
		int cnt = spf[i].second;
		while(j < n && cow[j].first <= spf[i].first) {
			que.push(cow[j].second);
			j++;
		}
		while(!que.empty() && cnt > 0) {
			int x = que.top(); que.pop();
			if(x < spf[i].first) continue;
			ans++;
			cnt--;
		}
	}
	cout << ans << endl;
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &cow[i].first, &cow[i].second);
	}
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &spf[i].first, &spf[i].second);
	}
	solve();
	
	return 0;
}
