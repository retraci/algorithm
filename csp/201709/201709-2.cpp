// 201709-2 公共钥匙盒
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxt = 11000;

int n, k;
int mt;
map<int, set<int> > mp1, mp2;
vector<int> bag;

int find(int val, int start) {
	for(int i = start; i < n; i++) {
		if(bag[i] == val) return i;
	}
}

void solve() {
	for(int i = 1; i <= n; i++) {
		bag.push_back(i);
	}
	
	set<int>::iterator it;
	for(int i = 1; i <= mt; i++) {

		if(mp2.count(i)) {
			int start = 0;
			for(it=mp2[i].begin(); it!=mp2[i].end(); it++) {
				int idx = find(0, start);
				bag[idx] = *it;
				start = idx+1;
			}
		}
		
		if(mp1.count(i)) {
			for(it=mp1[i].begin(); it!=mp1[i].end(); it++) {
				int idx = find(*it, 0);
				bag[idx] = 0;
			}
		}
	}
	
	for(int i = 0; i < bag.size()-1; i++) {
		printf("%d ", bag[i]);
	}
	cout << bag.back() << endl;
}

int main() {
	cin >> n >> k;
	
	int w, s, c;
	for(int i = 0; i < k; i++) {
		scanf("%d%d%d", &w, &s, &c);
		int t = s+c;
		mp1[s].insert(w);
		mp2[t].insert(w);
		mt = max(mt, t);
	}
	solve();
	
	return 0;
}
