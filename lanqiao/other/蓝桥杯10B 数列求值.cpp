// 蓝桥杯10B 数列求值
/*
	思路： 
	fibnacca 
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e4;

int fib[20190324] = {1,1,1};

int main() {
	for(int i = 3; i < 20190324; i++) {
		fib[i] = (fib[i-1]+fib[i-2]+fib[i-3]) % MOD;
	}
	cout << fib[20190324-1] << endl;
	
	return 0;
} 
