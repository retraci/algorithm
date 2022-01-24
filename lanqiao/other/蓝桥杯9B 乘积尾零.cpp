// 蓝桥杯9B 乘积尾零
/*
	思路：
	乘法中的 0 是由 2 * 5所得 
*/

#include <bits/stdc++.h>

using namespace std;

int cnt[2];

void count(int x) {
	int temp = x;
	while(x) {
		if(x%2 == 0) {
			cnt[0]++;
			x /= 2;
		} else {
			break;
		}
	}
	x = temp;
	while(x) {
		if(x%5 == 0) {
			cnt[1]++;
			x /= 5;
		} else {
			break;
		}
	}
}

int main() {
	int temp;
	for(int i = 0; i < 100; i++) {
		cin >> temp;
		
		count(temp);
	}
	
	cout << min(cnt[0], cnt[1]);
	
	return 0;
}
