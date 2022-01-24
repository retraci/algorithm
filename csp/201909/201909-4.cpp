// 201909-4
/*
	思路：
	思路：
	利用 set 的有序 
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long 

struct Node {
	long long id, val;
	Node(ll i_, ll v_) {
		id = i_, val = v_;
	}
	bool operator < (const Node &n2) const {
		if(val != n2.val) {
			return val > n2.val;
		} else {
			return id < n2.id;
		}
	}
};

const ll mul = 1e9;
const int maxm = 55;

int n, m;
set<Node> set1;
map<ll, set<Node>::iterator> mp;
int K[maxm];

ll get_id(ll type, ll x) {
	return type*mul+x;
}

void solve() {
	int T, op, k; 
	ll type, x, val;
	cin >> T;
	
	while(T--) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%I64d%I64d%I64d", &type, &x, &val);
			ll id = get_id(type, x);
			mp[id] = set1.insert(Node(id, val)).first;
		} else if(op == 2) {
			scanf("%I64d%I64d", &type, &x);
			ll id = get_id(type, x);
			set1.erase(mp[id]);
			mp.erase(id);
		} else {
			scanf("%d%", &k);
			for(int i = 0; i < m; i++) {
				scanf("%d", &K[i]);
			}
			vector<vector<int> > ans(m);
			set<Node>::iterator it;
			for(it = set1.begin(); it != set1.end(); it++) {
				int ty = (*it).id / mul;
				int id = (*it).id % mul;
				if(ans[ty].size() < K[ty]) {
					ans[ty].push_back(id);
					k--;
				}
				if(!k) break;
 			}
 			for(int i = 0; i < m; i++) 
			 	if(ans[i].empty()) ans[i].push_back(-1);
			for(int i = 0; i < m; i++) {
				for(int j = 0; j < ans[i].size(); j++) {
					printf("%d ", ans[i][j]);
				}
				cout << endl;
			}
		}
	}
}

int main() {
	cin >> m >> n;
	ll x, val;
	for(int i = 0; i < n; i++) {
		scanf("%I64d%I64d", &x, &val);
		for(int j = 0; j < m; j++) {
			ll id = get_id(j, x);
			mp[id] = set1.insert(Node(id, val)).first;
		}
	}
	solve();
	
	return 0;
}
