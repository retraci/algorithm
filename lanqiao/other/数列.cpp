// 数列
/*

*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const ll MOD = 7;

struct matrix {
	int r, c;
	ll s[5][5];
	matrix(int r = 0, int c = 0):r(r), c(c) {
		memset(s, 0, sizeof s);
	}
};

ll A, B, n;
matrix xi;
matrix f;

matrix operator*(const matrix &a, const matrix &b) {
	matrix c = matrix(a.r, b.c);
	for (int i = 0; i < c.r; i++) {
		for (int j = 0; j < c.c; j++) {
			for (int k = 0; k < a.c; k++) {
				c.s[i][j] = (c.s[i][j] + a.s[i][k] * b.s[k][j]) % MOD;
			}
		}
	}
	return c;
}

matrix power(matrix a, ll b) {
	matrix res = a;
	b--;
	while (b) {
		if(b & 1)
			res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

void init() {
	xi = matrix(2, 2);
	xi.s[0][0] = A; xi.s[0][1] = B;
	xi.s[1][0] = 1; xi.s[1][1] = 0;
	
	f = matrix(2, 1);
	f.s[0][0] = 1; 
	f.s[1][0] = 1;
}

void solve() {
	if (n == 1 || n == 2) {
		printf("%d\n", 1);
		return;	
	}
	
	init();
	xi = power(xi, n-2);
	
	f = xi * f;
	printf("%d\n", (f.s[0][0]) % MOD);
}

int main() {
	while (~scanf("%lld%lld%lld", &A, &B, &n) && (A || B || n)) {
		solve();
	}
	
	return 0;
}
