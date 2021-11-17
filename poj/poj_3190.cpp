// POJ 3190 Stall Reservations
/*
	思路：
	由于区间为 百万级别 不能采用开数组
	改用 优先队列模拟房间，先结束挤奶的牛优先级高
	如果有牛的开始时间大于优先级最高的牛的结束时间，则他们可以用同一间房
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct range {
	int left, right, pos;
	friend bool operator<(range r1, range r2) {
		if(r1.right == r2.right) return r1.left > r2.left;
		else return r1.right > r2.right;
	}
};

const int maxn = 5e5+10;

range cow[maxn];
int n;
int ans[maxn];

bool cmp(range r1, range r2) {
	if(r1.left == r2.left) return r1.right < r2.right;
	else return r1.left < r2.left;
}

void solve() {
	sort(cow, cow+n, cmp);
	int maxx = 1;
	priority_queue<range> que;
	que.push(cow[0]);
	ans[cow[0].pos] = 1;

	for(int i = 1; i < n; i++) {
		if(!que.empty() && cow[i].left > que.top().right) {
			ans[cow[i].pos] = ans[que.top().pos];
			que.pop();
			que.push(cow[i]);
		} else {
			maxx++;
			ans[cow[i].pos] = maxx;
			que.push(cow[i]);
		}
	}
	printf("%d\n", maxx);
	for(int i = 0; i < n; i++) {
		printf("%d\n", ans[i]);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &cow[i].left, &cow[i].right);
		cow[i].pos = i;
	}
	solve();

	return 0;
}
