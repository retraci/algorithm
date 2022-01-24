// 蓝桥杯 青蛙跳杯子 
/*
	思路：
	bfs
	
	map<string, bool> 记录状态 
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <map>

using namespace std;

struct state {
	string s;
	int step;
	state(string ss, int stt) : s(ss), step(stt){
	}
};

const int dx[6] = {-3,-2,-1,1,2,3};

string s1, s2;

void solve() {
	queue<state> que;
	que.push(state(s1, 0));
	map<string, bool> vis;
	
	while(!que.empty()) {
		state st = que.front(); que.pop();
//		cout << st.step << endl;
		string str = st.s;
		int x = str.find('*');
		
		for(int i = 0; i < 6; i++) {
			int nx = x+dx[i];
			if(nx >= 0 && nx < str.length()) {
				swap(str[x], str[nx]);
				if(str == s2) {
					cout << st.step+1 << endl;
					return;
				} else {
					if(!vis[str]) {
						que.push(state(str, st.step+1));
						vis[str] = true;
					}
				}
				swap(str[x], str[nx]);
			}
		}
	}
}

int main() {
	cin >> s1 >> s2;
	solve();
	
	return 0;
}
