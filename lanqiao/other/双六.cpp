// 双六
/*
	骰子的可能：a, b, -a, -b
	从 0 开始，能否到 1

	思路转化：
	x 个 a + y 个 b = 1，即
	x*a + y*b = 1;

	由于 gcd = 1，上式成立
	所以转化成
	a*x + b*y = gcd(a, b);
	下一步
	gcd(b, a%b) = b*x + (a%b)y

	因为，a%b = a-(a/b)*b
	带入得
	b*x + (a-(a/b)*b)*y
	化简得
	a*y + b*(x-(a/b))*y

	右边为上一轮的 x，y
	x -> y,
	y -> x-(a/b)*y;

	最终可以转化成求 gcd 的同时把 x，y 求出
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int extgcd(int a, int b, int &x, int &y) {
	int d;
	if(!b) {
		// 从最后回溯来推 
		x = 1, y = 0, d = a;
	} else {
		d = extgcd(b, a%b, y, x);
		cout << x << " " << y << endl;
		// 上一轮的 x，y 是调换的 
		y = y-(a/b)*x;
	}
	return d;
}

int main() {
	int a, b, x, y;
	cin >> a >> b;
	extgcd(a, b, x, y);
	printf("%d %d\n", x, y);

	return 0;
}
