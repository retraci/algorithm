// 201312-2
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int MOD = 11;

string str;

int cal() {
	int res = 0;
	int tmp = 1;
	for (int i = 0; i <= 10; i++) {
		if (str[i] == '-') continue;
		res = (res+(str[i]-'0')*tmp) % MOD;
		tmp++;
	}
	return res;
}

void solve() {
	int tmp = cal();

	char ch;
	if (tmp == 10) ch = 'X';
	else ch = '0'+tmp;

	if (ch == str[str.size()-1]) {
		cout << "Right" << endl;
	} else {
		str[str.size()-1] = ch;
		cout << str << endl;;
	}
}

int main() {
	cin >> str;
	solve();

	return 0;
}
