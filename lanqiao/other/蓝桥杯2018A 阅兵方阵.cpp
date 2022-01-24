// 蓝桥杯2018A 阅兵方阵
/*
	思路：
	枚举
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	for(int n = 1; ; n++) {

		int cnt = 0;
		for(int a = 1; a*a*2 <= n; a++) {
			int b = sqrt(n - a*a);
			if(a*a + b*b == n) {
				cnt++;
			}
			if(cnt >= 12) {
				cout << n << endl;
				exit(0);
			}
		}

	}

	return 0;
}
