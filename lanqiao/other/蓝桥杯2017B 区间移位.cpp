// 蓝桥杯2017B 区间移位
/*
	思路：
	二分答案 + 贪心
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int left, right;
	Node(int l_, int r_) {
		left = l_, right = r_;
	}
};

int n;
vector<Node> ns;

bool cmp(Node &n1, Node &n2) {
	if(n1.right == n2.right) return n1.left < n2.left;
	return n1.right < n2.right;
}

bool check(int x) {
	int mr = 0;
	vector<int> vis(n, 0);

	while(1) {
		int flag = 0;

		for(int i = 0; i < n; i++) {
			if(vis[i]) continue;
			if(mr <= ns[i].left && ns[i].left-x <= mr) {
				flag = 1;
				vis[i] = 1;
				int delta = ns[i].left - mr;
				mr = max(mr, ns[i].right - delta);
			} else if(mr > ns[i].left) {
				flag = 1;
				vis[i] = 1;
				int delta = mr - ns[i].left;
				delta = min(x, delta);
				mr = max(mr, ns[i].right + delta);
			}

			if(mr >= 20000) return true;
		}
		
		if(!flag) break;
	}

	return false;
}

void solve() {
	sort(ns.begin(), ns.end(), cmp);
	int left = 0, right = 100000;

	int ans = 100000;
	while(left <= right) {
		int mid = (left+right) / 2;
		if(check(mid)) {
			ans = mid;
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}

	cout << ans/2.0 << endl;
}

int main() {
	cin >> n;

	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		ns.push_back(Node(a*2, b*2));
	}
	solve();

	return 0;
}
