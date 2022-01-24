// 蓝桥杯2019B E
/*
	思路：
	枚举 
*/

#include <bits/stdc++.h>
#pragma optimize(2)

using namespace std;

int main() {
	int n = 100;
	
	for(int i = 1; ; i++) {
		int cnt = 0;
		for(int j = 1; j <= i; j++) {
			if(i % j == 0) cnt++;
		}
		if(cnt == n) {
			cout << i << endl;
			return 0;
		}
	}
	
	return 0;
}
