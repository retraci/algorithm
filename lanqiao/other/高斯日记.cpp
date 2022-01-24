// 蓝桥杯 高斯日记
/*
	思路：
	模拟 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int md[13] = {0,31,30,31,30,31,30,31,31,30,31,30,31};
int y, m, d, n;

bool is_run(int year) {
	if(year%4==0 && year%100!=0) return true;
	if(year%400 == 0) return true;
	return false;
}

void solve() {
	if(is_run(y)) md[2] = 29;
	else md[2] = 28;
	
	for(int i = 0; i < n; i++) {
		if(d == md[m]) {
			if(m == 12) {
				d = 1; m = 1; y++;
				if(is_run(y)) md[2] = 29;
				else md[2] = 28;
			} else {
				d = 1; m++;
			}
		} else {
			d++;
		}
	}
	printf("%d-%02d-%02d\n", y, m, d);
}

int main() {
	scanf("%d-%d-%d", &y, &m, &d);
	scanf("%d", &n);
	solve();

	return 0;
}
