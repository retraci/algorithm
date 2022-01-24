// 蓝桥杯 核桃的数量 
/*
	思路：
	gcd 
*/ 

#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
	if(a < b) swap(a, b);
	return b==0? a: gcd(b, a % b);
}

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	int temp1 = a*b/gcd(a, b);
	int temp2 = gcd(temp1, c);
	int ans = temp1*c/temp2;
	
	cout << ans << endl;
	
	return 0;
}
