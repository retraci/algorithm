// 线段上的格子数 
/*
	P1(x1, y1), P2(x2, y2)
	线段 P1P2 上有多少格子
	
	求 gcd(x2-x1, y2-y1)
	
	解析，将 x2-x1, y2-y1 分成 gcd 份
	画出网格图，作图发现，ans = gcd-1 
*/ 

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
	if(!b) return a;
	else return gcd(b, a%b);
}

int main() {
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	
	int ans = gcd(max(y2-y1, x2-x1), min(y2-y1, x2-x1)) - 1;
	cout << ans << endl;
	
	return 0;
}
