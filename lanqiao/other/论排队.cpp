// 论排队
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

int n;
string mp1[maxn]; 
unordered_map<string, int> mp2;

unordered_set<string> vis;
int du[maxn];
vector<int> G[maxn];

void nameToIdx(string name, int idx) {
	mp1[idx] = name;
	mp2[name] = idx;
}

void solve() {
//	for(int i = 0; i < n; i++) {
//		for(int j = 0; j < G[i].size(); j++) {
//			cout << mp1[i] << " " << mp1[G[i][j]] << " ";
//		}
//		cout << endl;
//	}
	
	vector<int> ans;
	queue<int> que;
	for(int i = 0; i < n; i++) {
		if(mp1[i] == "@") {
			que.push(i);
			break;
		}
	}
	for(int i = 0; i < n; i++) {
		if(!du[i] && mp1[i] != "@") que.push(i);
	}
		
	while(!que.empty()) {
		int u = que.front(); que.pop();
		ans.push_back(u);
		for(int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if(du[v] > 0) {
				du[v]--;
				if(du[v] == 0) {
					que.push(v);
				}
			}
		}
	}
	for(int i = 0; i < n; i++) {
		if(mp1[ans[i]] == "@" || mp1[ans[i]] == "#") continue;
		cout << mp1[ans[i]] << " ";
	}
}

int main() {
	cin >> n;
	int pos = 0;
	
	string a, b;
	memset(du, 0, sizeof(du));
	for(int i = 0; i < n; i++) {
		cin >> a >> b;
		if(a == "#") a = "@";
		
		if(!vis.count(a)) {
			nameToIdx(a, pos++);
			vis.insert(a);
		}
		if(!vis.count(b)) {
			nameToIdx(b, pos++);
			vis.insert(b);
		}
		
		int idxa = mp2[a];
		int idxb = mp2[b];
		G[idxa].push_back(idxb);
		du[idxb]++;
	}
	n += 2;
	solve();
	
	return 0;
}
