// 蓝桥杯2014B 排列序数 
/*
	思路：
	dfs 
*/

#include <bits/stdc++.h>

using namespace std;

int n, cnt;
string s;
int vis[11];

void dfs(string now, int x) {
	if(x == n) {
		if(now == s) {
			cout << cnt << endl;
		}
		cnt++;
	}
	
	for(int i = 0; i < n; i++) {
		if(vis[i]) continue;
		vis[i] = 1;
		now[x] = 'a'+i;
		dfs(now, x+1);
		vis[i] = 0;
 	}
}

int main() {
	cin >> s;
	n = s.size();
	
	string now = "";
	for(int i = 0; i < n; i++) now += 'a'+i;
	
	int cnt = 0;
	do {
		if(now == s) cout << cnt << endl;
		cnt++;
	} while(next_permutation(now.begin(), now.end()));
	
//	dfs(now, n);
	
	return 0;
}
