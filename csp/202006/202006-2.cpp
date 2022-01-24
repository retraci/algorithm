// 202006-2
/*

*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Node {
	ll idx, val;
	Node(ll i_, ll v_) {
		idx = i_, val = v_;
	}
};

int n;
vector<Node> v1, v2;

void solve() {
	ll ans = 0;
	int p1 = 0, p2 = 0;
	
	while(p1 < v1.size() && p2 < v2.size()) {
		if(v1[p1].idx == v2[p2].idx) {
			ans += v1[p1++].val * v2[p2++].val;
		} else if(v1[p1].idx < v2[p2].idx) {
			p1++;
		} else {
			p2++;
		}
	}
	cout << ans << endl;
}

int main() {
	int a, b;
	cin >> n >> a >> b;
	
	int tmp1, tmp2;
	for(int i = 0; i < a; i++) {
		scanf("%d%d", &tmp1, &tmp2);
		v1.push_back(Node(tmp1, tmp2));
	}
	for(int i = 0; i < b; i++) {
		scanf("%d%d", &tmp1, &tmp2);
		v2.push_back(Node(tmp1, tmp2));
	}
	solve();
	
	return 0;
} 
