// 棋盘游戏
/*
	思路：
	双向 bfs 
*/

/*
1111
0000
0000
0000

1000
0111
0000
0000
*/

#include <bits/stdc++.h>

using namespace std;

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

string s, tar;

bool inBound(int x, int y) {
	return x>=0 && x<4 && y>=0 && y<4;
}

int get_idx(int x, int y) {
	return x*4+y;
}

void print(string &s) {
	cout << endl;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			int idx = get_idx(i, j);
			cout << s[idx];
		}
		cout << endl;
	}
}

int bfs() {
	unordered_set<string> set1, set2, temp;
	unordered_set<string> vis;
	set1.insert(s);
	set2.insert(tar);

	int res = 0;
	while(!set1.empty() && !set2.empty()) {
		if(set1.size() > set2.size()) {
			temp = set1, set1 = set2, set2 = temp;
		}
		
		temp.clear();
		for(auto it = set1.begin(); it != set1.end(); it++) {
			string cur = *it;
			if(set2.count(cur)) return res;

			if(vis.count(cur)) continue;
			vis.insert(cur);

			string ns = cur;
			for(int i = 0; i < 15; i++) {
				if(ns[i] == '0') continue;
				int x = i / 4;
				int y = i % 4;

				for(int j = 0; j < 4; j++) {
					int nx = x + dx[j];
					int ny = y + dy[j];
					int ni = get_idx(nx, ny);

					if(inBound(nx, ny) && ns[i] != ns[ni]) {
						swap(ns[i], ns[ni]);
						temp.insert(ns);
						swap(ns[i], ns[ni]);
					}
				}
			}
		}

		res++;
		set1 = temp;
	}
	return -1;
}

void solve() {
	cout << bfs() << endl;
}

int main() {
	string tmp;
	for(int i = 0; i < 4; i++) {
		cin >> tmp;
		s += tmp;
	}
	for(int i = 0; i < 4; i++) {
		cin >> tmp;
		tar += tmp;
	}
	solve();

	return 0;
}
