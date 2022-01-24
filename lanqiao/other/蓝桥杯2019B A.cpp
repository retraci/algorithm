// 蓝桥杯2019B A 
/*
	思路：
	枚举 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	for(int len = 2020; ; len++) {
		for(int x = 2020; ; x++) {
			int y = len - x;
			if(y < x || x < 2019) break;
			if(x*x - 2019*2019 == y*y-x*x) {
				printf("%d %d %d\n", x, y, len);
			}
		}
	}
	
	return 0;
} 
