// 蓝桥杯11B 整除序列
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	long long n;
	cin >> n;
	while(n) {
		cout << n;
		n >>= 1;
		if(n == 0) cout << endl;
		else cout << " ";
	}
	
	return 0;
} 
