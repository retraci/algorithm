// 规则括号
/*

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	string str;
	cin >> str;

	stack<char> stk;
	int ans = 0;
	for(char &ch: str) {
		if(ch == '(') {
			stk.push('1');
		} else {
			if(!stk.empty()) {
				stk.pop();
				ans += 2;
			}
		}
	}
	cout << ans << endl;

	return 0;
}
