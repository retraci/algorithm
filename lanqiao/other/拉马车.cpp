// 蓝桥杯 拉马车
/*
	思路：
	栈模拟，map记录 
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
#include <map>

using namespace std;

string s1, s2;
map<char, bool> vis;
stack<char> st;

void solve() {
	bool round = true;
	
	while(s1.length() && s2.length()) {
		if(round) {
			st.push(s1[0]);
			s1.erase(s1.begin());
			if(!vis[st.top()]) {
				vis[st.top()] = true;
			} else {
				char temp = st.top();
				vis[st.top()] = false;
				s1 += st.top();
				st.pop();

				while(st.top() != temp) {
					vis[st.top()] = false;
					s1 += st.top();
					st.pop();
				}
				vis[st.top()] = false;
				s1 += st.top();
				st.pop();
				// 赢牌的一方继续出牌 
				round = !round;
			}
		} else {
			st.push(s2[0]);
			s2.erase(s2.begin());
			if(!vis[st.top()]) {
				vis[st.top()] = true;
			} else {
				char temp = st.top();
				vis[st.top()] = false;
				s2 += st.top();
				st.pop();

				while(st.top() != temp) {
					vis[st.top()] = false;
					s2 += st.top();
					st.pop();
				}
				vis[st.top()] = false;
				s2 += st.top();
				st.pop();
				round = !round;
			}
		}
		round = !round;
	}

	if(s1.length()) {
		cout << s1 << endl;
	} else {
		cout << s2 << endl;
	}
}

int main() {
	cin >> s1 >> s2;
	solve();

	return 0;
}
