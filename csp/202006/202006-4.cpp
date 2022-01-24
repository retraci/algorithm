// 202006-4
/*
	思路：
	矩阵快速幂 优化dp 
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll MOD = 998244353;

struct matrix {
	int r, c;
	ll s[15][15];
	matrix(int r = 0, int c = 0):r(r), c(c) {
		memset(s, 0, sizeof s);
	}
};

int n;
string s;
map<string, int> mp;
matrix xi;
matrix f;

matrix operator*(const matrix &a, const matrix &b) {
	matrix c = matrix(a.r, b.c);
	for (int i = 0; i < c.r; i++) {
		for (int j = 0; j < c.c; j++) {
			for (int k = 0; k < a.c; k++) {
				c.s[i][j] += a.s[i][k] * b.s[k][j];
			}
			c.s[i][j] %= MOD;
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
	mp["1"] = 1; mp["2"] = 2; mp["4"] = 3; mp["6"] = 4;
	mp["16"] = 5; mp["64"] = 6; mp["26"] = 7; mp["41"] = 8;
	mp["62"] = 9; mp["46"] = 10; mp["44"] = 11; mp["66"] = 12;
	mp["61"] = 13; mp["42"] = 14; 
	
	xi = matrix(15, 15);
	for (int i = 0; i < xi.r; i++) 
		for (int j = 0; j < xi.c; j++)
			xi.s[i][j] = 0;
	
	xi.s[1][3] = 1;
	xi.s[2][1] = 1;
	xi.s[3][2] = xi.s[3][4] = 1;
	xi.s[4][3] = xi.s[4][4] = 1;
	xi.s[5][3] = 1;
	xi.s[6][4] = xi.s[6][14] = 1;
	xi.s[7][5] = 1;
	xi.s[8][6] = 1;
	xi.s[9][8] = 1;
	xi.s[10][7] = xi.s[10][12] = 1;
	xi.s[11][9] = 1;
	xi.s[12][10] = 1;
	xi.s[13][11] = 1;
	xi.s[14][13] = 1;
	
	f = matrix(15, 1);
	for (int i = 0; i < f.r; i++) 
		for (int j = 0; j < f.c; j++)
			f.s[i][j] = 0;
	f.s[1][0] = 1;
}

void solve() {
	init();
	if (n == 0) {
		printf("%I64d\n", f.s[mp[s]][0]);
		return;
	}
	
	xi = power(xi, n);
	
	f = xi * f;
	printf("%I64d\n", f.s[mp[s]][0]);
}

int main() {
	while (cin >> n >> s) {
		solve();
	}
	
	return 0;
}
