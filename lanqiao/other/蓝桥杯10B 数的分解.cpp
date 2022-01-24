// 蓝桥杯10B 数的分解
/*
	思路： 
	枚举 
*/

#include <bits/stdc++.h>

using namespace std;

bool check(int x) {
	while(x) {
		int temp = x % 10;
		if(temp == 2 || temp == 4) return false;
		x /= 10;
	}
	return true;
}

int main() {
	int tar = 2019;
	long long ans = 0;
	
	for(int i = 1; i < tar; i++) {
		if(check(i))
		for(int j = i+1; j < tar; j++) {
			if(check(j))
			for(int k = j+1; k < tar; k++) {
				if(check(k))
				if(i+j+k == tar) ans++; 
			}
		}
	}
	cout << ans << endl;
	
	return 0;
}
