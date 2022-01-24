// 蓝桥杯2018B 换零钞 
/*
	思路：
	枚举 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int tot = 200;
	for(int i = 1; i < 200; i++) {
		for(int j = 1; j < 200;j++) {
			int k = 10 * j;
			if(i*5+j+2*k == tot) cout << i+j+k << endl;
		}
	} 
	
	return 0; 
} 
