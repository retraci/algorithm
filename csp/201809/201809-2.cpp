// 201809-2
/*
	思路:
	枚举 
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
vector<Node> v1, v2;

/*
4
1 3
5 6
9 13
14 15
2 4
5 7
10 11
13 14
*/

void solve() {
	long long ans = 0;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int left1 = v1[i].left;
			int right1 = v1[i].right;
			int left2 = v2[j].left;
			int right2 = v2[j].right;
			
			if(right1 <= left2 || left1 >= right2) continue;
			int left = max(left1, left2);
			int right = min(right1, right2);
			ans += right - left; 
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n;
	
	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		v1.push_back(Node(a, b));
	}
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		v2.push_back(Node(a, b));
	}
	solve();
	
	return 0;
}
