// 蓝桥杯2013B 猜灯谜
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int a, b, c;
int d, e, f;

int get_num1() {
	int res = a;
	res = res*10 + b;
	res = res*10 + c;
	
	return res;
}

int get_num2() {
	int res = a;
	res = res*10 + d;
	res = res*10 + e;
	res = res*10 + f;
	res = res*10 + d;
	res = res*10 + b;
	
	return res;
}

int main() {

	for(a = 0; a <= 9; a++) {
		for(b = 0; b <= 9; b++) {
			for(c = 0; c <= 9; c++) {
				for(d = 0; d <= 9; d++) {
					for(e = 0; e <= 9; e++) {
						for(f = 0; f <= 9; f++) {
							int num1 = get_num1();
							int num2 = get_num2();
							if(num1 * num1 == num2) cout << num1 << endl;
						}
					}
				}
			}
		}
	}
	
	
	return 0;
} 
