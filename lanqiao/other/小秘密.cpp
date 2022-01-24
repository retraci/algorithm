// 小秘密
/*

*/

#include <bits/stdc++.h>

using namespace std;

string str;

void solve() {
	string p = "xihui";
	int now = 0;
	
	for(int i = 0; i < str.size(); i++) {
		if(str[i] == p[now]) {
			now++;
		}
		if(now == 5) {
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
}

int main() {
	cin >> str;
	solve();	
	
	return 0;
}
