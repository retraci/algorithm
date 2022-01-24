// 蓝桥杯2017B 平方十位数 
/*
	思路：
	全排列 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int a[10] = {9,8,7,6,5,4,3,2,1,0};
	do {
		long long num = 0;
		for(int i = 0; i < 10; i++) {
			num *= 10;
			num += a[i];
		}
		if(floor(sqrt(num)) == sqrt(num)) {
			cout << num << endl << sqrt(num);
			return 0;
		}
	} while(prev_permutation(a, a+10));
	
	return 0;
} 
