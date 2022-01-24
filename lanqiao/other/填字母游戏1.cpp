// 蓝桥杯 填字母游戏
/*
	思路：
	博弈论
	
	node:
	map 记录情况
	必胜情况 剪枝 
	
	递归出口:
	必胜情况 
	平手情况
	必输情况 
*/

#include <bits/stdc++.h>

using namespace std;

const char ch[2] = {'L','O'};

int n;
map<string, int> mp;

int game(string s) {
	if(n < 3) return 0;
	if(mp.find(s) != mp.end()) return mp[s];
	if(s.find("*OL")!=-1 || s.find("L*L")!=-1 || s.find("LO*")!=-1) {
		mp[s] = 1;
		return 1;
	}
	if(s.find("LOL")!=-1) {
		mp[s] = -1;
		return -1;
	}
	if(s.find("*")==-1 && s.find("LOL")==-1) {
		mp[s] = 0;
		return 0;
	}

	int ping = 0;
	for(int i = 0; i < n; i++) {
		if(s[i] == '*') {
			for(int j = 0; j < 2; j++) {
				string ns = s;
				ns[i] = ch[j];

				if(ns.find("*OL")!=-1 || ns.find("L*L")!=-1 || ns.find("LO*")!=-1) {
					continue;
				}

				int flag = game(ns);
				if(flag == -1) {
					mp[s] = 1;
					return 1;
				} else if(flag == 0) {
					ping = 1;
				}
			}
		}
	}
	if(ping) {
		mp[s] = 0;
		return 0;
	}

	mp[s] = -1;
	return -1;
}

int main() {
	string temp;
	int T;
	cin >> T;
	while(T--) {
		cin >> temp;
		n = temp.length();
		cout << game(temp) << endl;
	}

	return 0;
}
