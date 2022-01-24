// 蓝桥杯2014B 国王的遗产
/*
	思路：
	模拟
*/

#include <bits/stdc++.h>

using namespace std;

bool check(int x) {
	if(x%4 != 0) return false;
	if(x%5 != 0) return false;
	if(x%6 != 0) return false;
	if(x%7 != 0) return false;
	if(x%8 != 0) return false;
	if(x%9 != 0) return false;

	return true;
}

int main() {
	for(int i = 12; i < 10000; i++) {
		if(check(i)) {
			int sum = i - i/4 - i/5 - i/6 - i/7 - i/8 - i/9;
			if(sum == 11) cout << i << endl;
		}
	}
	return 0;
}
