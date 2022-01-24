// 蓝桥杯 数字游戏 
/*
	思路：
	数学规律题 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

long long n, k, T;

void solve() {
	long long ans = 1;
	long long last = 1;
	
	for(int i = 1; i < T; i++) {
		long long now = (last+((i-1)*n+1+i*n)*n/2) % k;
		ans += now;
		last = now;
	}
	cout << ans << endl;
}

int main() {
	cin >> n >> k >> T;
	solve();
	
	return 0;
}
