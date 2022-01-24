// 蓝桥杯 回文数字
/*
	思路：
	枚举
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

int n;

int get_sum(int x) {
	int res = 0;
	while(x) {
		res += x%10;
		x /= 10;
	}
	return res;
}

string toString(int x) {
	string res = "";
	while(x) {
		res += x%10;
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

bool is_hw(string s) {
	int l = 0, r = s.length()-1;
	
	while(l < r) {
		if(s[l++] != s[r--]) return false;
	}
	return true;
}

void solve() {
	int flag = 0;
	for(int i = 1e4; i < 1e6; i++) {
		int sum = get_sum(i);
		if(sum == n && is_hw(toString(i))) {
			flag = 1;
			printf("%d\n", i);
		}
	}
	if(!flag) printf("-1\n");
}

int main() {
	cin >> n;
	solve();
	
	return 0;
}
