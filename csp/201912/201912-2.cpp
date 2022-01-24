// 201912-2
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;
const int dx[8] = {0,0,-1,1,-1,-1,1,1};
const int dy[8] = {-1,1,0,0,-1,1,-1,1};

int n;
int xs[maxn], ys[maxn];
int val[5];

bool check(int a) {
	int cnt = 0;
	int x = xs[a];
	int y = ys[a];
	for(int k = 0; k < 4; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		for(int i = 0; i < n; i++) {
			if(nx == xs[i] && ny == ys[i]) {
				cnt++;
				break;
			}
		}
	}
	
	return cnt==4;
}

int cal(int a) {
	int cnt = 0;
	int x = xs[a];
	int y = ys[a];
	for(int k = 4; k < 8; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		for(int i = 0; i < n; i++) {
			if(nx == xs[i] && ny == ys[i]) {
				cnt++;
				break;
			}
		}
	}
	return cnt;
}

void solve() {
	for(int i = 0; i < n; i++) {
		if(check(i)) {
			val[cal(i)]++;
		}
	}
	for(int i = 0; i < 5; i++) cout << val[i] << endl;
}

int main() {
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &xs[i], &ys[i]);
	}
	solve();
	
	return 0;
}
