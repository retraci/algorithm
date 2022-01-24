// 蓝桥杯2018B 调手表
/*
	思路：
	bfs
*/

#include <bits/stdc++.h>
#pragma optimize(2)

using namespace std;

const int maxn = 100010;

int cs[maxn];

int main() {
	int n, k;
	cin >> n >> k;
	memset(cs, -1, sizeof(cs));

	queue<int> que;
	que.push(0);
	cs[0] = 0;
	while(!que.empty()) {
		int now = que.front(); que.pop();
		int a = (now + 1) % n;
		if(cs[a] == -1) {
			cs[a] = cs[now] + 1;
			que.push(a);
		}
		int b = (now + k) % n;
		if(cs[b] == -1) {
			cs[b] = cs[now] + 1;
			que.push(b);
		}
	}
	int ans = 0;
	for(int i = 0; i < n; i++) ans = max(ans, cs[i]);
	cout << ans << endl;
	
	return 0;
}
