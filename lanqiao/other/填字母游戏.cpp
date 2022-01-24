// 蓝桥杯 填字母游戏
/*
	思路：
	博弈论
	
	模板：
	if mp 里有则 	返回
	if 必赢局面	 	返回 
	if 必输局面  	返回 
	if 打平局面  	返回 
	
	for 获取下一个局面
		如果下一个局面必赢  跳过
		如果下一个局面打平  记录
		如果下一个局面必输  返回 
	end for
	
	if 打平  记录，返回 
	记录必输局面  返回 
		 
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

const char dir[2] = {'L', 'O'};

int n;
map<string, int> mp;

int game(string s) {
	if(s.length() < 3) return 0;
	if(mp.find(s)!=mp.end()) return mp[s];
	// 剪枝 
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
	for(int i = 0; i < s.length(); i++) {
		if(s[i] == '*') {
			for(int j = 0; j < 2; j++) {
				s[i] = dir[j];
				// 剪枝
				if(s.find("*OL")!=-1 || s.find("L*L")!=-1 || s.find("LO*")!=-1) {
					s[i] = '*';
					continue;
				}
				int flag = game(s);
				s[i] = '*';
				if(flag == 0) {
					ping = 1;
				} else if(flag == -1) {
					mp[s] = 1;
					return 1;
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
	cin >> n;
	string s;
	while(n--) {
		cin >> s;
		cout << game(s) << endl;
	}

	return 0;
}
