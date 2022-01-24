// 蓝桥杯8B 等差素数列 
/*
	思路：
	埃氏筛数 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6;

int isP[maxn];

int main() {
	memset(isP, 1, sizeof(isP));
	
	for(int i = 2; i < maxn; i++) {
		if(isP[i])
		for(int k = 2; k*i < maxn; k++) {
			isP[i*k] = 0;
		}
	}
	
	for(int s = 2; s < maxn; s++) {
		if(isP[s])
		for(int d = 1; d < maxn; d++) {
			int flag = 0;
			for(int i = 1; i <= 9; i++) {
				if(s+d*i >= maxn || !isP[s+d*i]) {
					flag = 1;
					break;
				}
			}
			if(!flag) {
				cout << d << endl;
				return 0;
			}
		}
	}
	
	return 0;
}
