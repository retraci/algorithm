// 蓝桥杯2013B 连续奇数和
/*
	思路：
	模拟
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = 111*111*111;

	for(int i = 1; i <= n; i+=2) {
		for(int k = 1; k <= n; k++) {
			int j = i+2*(k-1);
			int sum = (i+j)*k/2;
			if(sum == n) {
				printf("%d %d\n", i, j);
			} else if(sum > n) {
				break;
			}
		}
	}

	return 0;
}
