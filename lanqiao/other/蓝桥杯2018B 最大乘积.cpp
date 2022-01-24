// 蓝桥杯2018B 最大乘积
/*
	思路：
	全排列 
*/

#include <bits/stdc++.h>

using namespace std;

int a[9] = {9,8,7,6,5,4,3,2,1};
long long ans;

void cal() {
	for(int len = 1; len < 9; len++) {
		long long left = 0;
		for(int j = 0; j < len; j++) {
			left *= 10;
			left += a[j];
		}
		
		long long right = 0;
		for(int j = len; j < 9; j++) {
			right *= 10;
			right += a[j];
		}
		
		long long temp = right * left;
		if(temp >= 1e9 || temp <= 1e8) return;
		
		set<int> set1;
		while(temp) {
			set1.insert(temp%10);
			temp /= 10;
		}
		if(set1.count(0) == 0 && set1.size() == 9) {
			ans = max(ans, right*left);
		}
	}
}

int main() {
//	do {
//		cal();
//	} while(prev_permutation(a, a+9));
	ans = 839542176;
	cout << ans << endl;
	
	return 0;
}
