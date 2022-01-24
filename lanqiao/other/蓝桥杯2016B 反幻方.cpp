// 蓝桥杯2016B 反幻方
/*
	思路：
	dfs 全排列
*/

#include <bits/stdc++.h>

using namespace std;

int a[9] = {1,2,3,4,5,6,7,8,9};

bool check() {
	int a1 = a[0]+a[1]+a[2];
	int a2 = a[3]+a[4]+a[5];
	int a3 = a[6]+a[7]+a[8];

	int a4 = a[0]+a[3]+a[6];
	int a5 = a[1]+a[4]+a[7];
	int a6 = a[2]+a[5]+a[8];
	
	int a7 = a[0]+a[4]+a[8];
	int a8 = a[2]+a[4]+a[6];
	
	if(a1 == a2 || a1 == a3 || a1 == a4 || a1 == a5 || a1 == a6 || a1 == a7 || a1 == a8) return false;
	if(a2 == a3 || a2 == a4 || a2 == a5 || a2 == a6 || a2 == a7 || a2 == a8) return false;
	if(a3 == a4 || a3 == a5 || a3 == a6 || a3 == a7 || a3 == a8) return false;
	if(a4 == a5 || a4 == a6 || a4 == a7 || a4 == a8) return false;
	if(a5 == a6 || a5 == a7 || a5 == a8) return false;
	if(a6 == a7 || a6 == a8) return false;
	if(a7 == a8) return false;
	
	return true;
}

int main() {
	int ans = 0;
	do {
		if(check()) ans++;
	} while(next_permutation(a, a+9));
	cout << ans/8 << endl;

	return 0;
}
