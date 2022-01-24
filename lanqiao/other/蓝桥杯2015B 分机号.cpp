// 蓝桥杯2015B 分机号 
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

bool check(int x) {
	int a = x % 10;
	int b = (x / 10) % 10;
	int c = x / 100;
	
	if(a >= b || b >= c || a >= c) return false;
	return true;
}

int main() {
	int ans = 0;
	
	for(int i = 100; i <= 999; i++) {
		if(check(i)) {
			ans++;
			//cout << i << endl;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
