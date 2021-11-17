// POJ 3181 Dollar Dayz
/*
	思路：
	完全背包 + 高精度 
	
	note:
	1. 先遍历商品，再遍历背包 （背包大小 从小到大       01背包则从大到小 
	
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1010;
const int maxk = 110;

int n, k;
long long a[maxk][maxn], b[maxk][maxn];

int main() {
	cin >> n >> k;
	
	long long inf = 1;
	for(int i = 0; i < 18; i++) inf *= 10;
	
	for(int i = 0; i <= k; i++) a[i][0] = 1;
	
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j <= n; j++) {
			if(i > j) {
				a[i][j] = a[i-1][j];
				b[i][j] = b[i-1][j];
			} else {
				a[i][j] = (a[i-1][j] + a[i][j-i]) % inf;
				b[i][j] = b[i-1][j] + b[i][j-i] + (a[i-1][j] + a[i][j-i]) / inf;
			}
		}
	}
	if(b[k][n]) cout << b[k][n];
	cout << a[k][n] << endl;
	
	return 0;
}

