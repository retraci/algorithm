// POJ 1065 Wooden Sticks

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

struct node {
	int l, w;
	
	node(int ll, int ww):l(ll), w(ww){
	}
};

int n;
vector<node> v;
vector<int> x, y;

bool cmp(node n1, node n2) {
	if(n1.l == n2.l) return n1.w < n2.w;
	return n1.l < n2.l;
}

void solve() {
	sort(v.begin(), v.end(), cmp);
	
//	for(node &t : v) {
//		printf("%d %d\n", t.l, t.w);
//	}
	int ans = 0;
	for(int i = 0; i < n; i++) {
		int flag = 0;
		for(int j = 0; j < ans; j++) {
			if(x[j]<=v[i].l && y[j]<=v[i].w) {
				flag = 1;
				x[j] = v[i].l; y[j] = v[i].w;
				break;
			}
		}
		if(!flag) {
			ans++;
			x.push_back(v[i].l);
			y.push_back(v[i].w);
		}
	}
	cout << ans << endl;
}

int main() {
	int T;
	cin >> T;
	
	while(T--) {
		v.clear();
		x.clear();
		y.clear();
		scanf("%d", &n);
		
		for(int i = 0; i < n; i++) {
			int t1, t2;
			scanf("%d %d", &t1, &t2);
			v.push_back(node(t1, t2));
		}
		
		solve();
	}
	
	return 0;
}
