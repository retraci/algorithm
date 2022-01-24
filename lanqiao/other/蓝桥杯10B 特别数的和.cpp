// 蓝桥杯10B 特别数的和 
/*
	思路：
	枚举 
*/

#include <bits/stdc++.h>

using namespace std;

bool check(int x) {
	while(x) {
		int temp = x % 10;
		if(temp == 2 || temp == 0 || temp == 1 || temp == 9) return true;
		x /= 10;
	}
	return false;
}

int main() {
	int n, ans = 0;
	cin >> n;
	
	for(int i = 1; i <= n; i++) {
		if(check(i)) {
			ans += i;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
