// POJ 3126 Prime Path
/*
	Ë¼Â·£º
	°£É¸ 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>

using namespace std;

const int maxn = 10000;

vector<int> prime;
int a, b;
int vis[maxn];

bool check(int x, int y) {
	int x1 = x%10, y1 = y%10;
	int x2 = (x/10)%10, y2 = (y/10)%10;
	int x3 = (x/100)%10, y3 = (y/100)%10;
	int x4 = x/1000, y4 = y/1000;
	
	int cnt = 0;
	if(x1 != y1) cnt++;
	if(x2 != y2) cnt++;
	if(x3 != y3) cnt++;
	if(x4 != y4) cnt++;
	
	return cnt==1;
}

void solve() {
	memset(vis, false, sizeof(vis));
	queue<int> que;
	que.push(a);

	int cnt = 0;
	while(!que.empty()) {
		int len = que.size();
		
		for(int k = 0; k < len; k++) {
			int cur = que.front(); que.pop();

			if(cur == b) {
				cout << cnt << endl;
				return;
			}
			
			if(vis[cur]) continue;
			vis[cur] = true;
			
			for(int i = 0; i < prime.size(); i++) {
				if(check(cur, prime[i])) 
					que.push(prime[i]);
			}
		}
		
		cnt++;
	}
	cout << "Impossible" << endl;
}

int main() {
	int temp[10000];
	for(int i = 2; i < 10000; i++) {
		temp[i] = 1;
	}
	for(int i = 2; i < 10000; i++) {
		if(temp[i]) {
			for(int k = 2; k*i < 10000; k++) {
				temp[k*i] = 0;
			}
		}
	}
	for(int i = 1000; i < 10000; i++) {
		if(temp[i]) prime.push_back(i);
	}

	int T;
	cin >> T;

	while(T--) {
		cin >> a >> b;
		solve();
	}

	return 0;
}
