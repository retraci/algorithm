// 蓝桥杯2017B 填字母游戏 
/*
	思路：
	博弈游戏，dfs 
	记忆性搜索 
	
	node:
	dfs 的下一状态用新的变量保存 
*/

#include <bits/stdc++.h>

using namespace std;

map<string, int> memo;

int dfs(string s) {
	if(s.size() < 3) return 0;
	
	if(memo.count(s)) return memo[s];
	if(s.find("LOL") != string::npos) return memo[s]=-1;
	if(s.find("*OL") != string::npos) return memo[s]=1;
	if(s.find("L*L") != string::npos) return memo[s]=1;
	if(s.find("LO*") != string::npos) return memo[s]=1;
	if(s.find("*") == string::npos) return memo[s]=0;
	
	int res = -1;
	for(int i = 0; i < s.size(); i++) {
		if(s[i] != '*') continue;
		string ns = s;
		
		ns[i] = 'L';
		int temp = dfs(ns);
		if(temp == -1) return memo[s]=1;
		if(temp == 0) res = 0;
		
		ns[i] = 'O';
		temp = dfs(ns);
		if(temp == -1) return memo[s]=1;
		if(temp == 0) res = 0;
		
	}
	
	return memo[s]=res;
}

int main() {
	int n;
	string s;
	
	cin >> n;
	while(n--) {
		cin >> s;
		cout << dfs(s) << endl;
	}
	
	return 0;
}
