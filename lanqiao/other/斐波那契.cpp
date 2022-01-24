// 蓝桥杯 斐波那契
/*
	思路：
	数学推导 + 矩阵快速幂 
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

struct mat {
	ll x[2][2];
};

ll n, m, p;
mat A = {1,1,1,0};
mat E = {1,0,0,1};

// 快速乘 
ll mult(ll a, ll b) {
	ll res = 0;
	a %= p; b %= p;
	if(a > b) swap(a, b);
	
	while(b) {
		if(b & 1) res = (res + a) % p;
		a = (a << 1) % p;
		b >>= 1;
	}
	return res;
}

mat mat_mult(mat a, mat b) {
	mat res;
	
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			res.x[i][j] = 0;
			for(int k = 0; k < 2; k++) {
				res.x[i][j] += mult(a.x[i][k], b.x[k][j]);
				res.x[i][j] %= p;
			}
		}
	}
	return res;
}

mat mat_pow(mat A, ll n) {
	mat res = E, base = A;
	
	while(n) {
		if(n & 1) res = mat_mult(res, base);
		n >>= 1;
		base = mat_mult(base, base);
	}
	return res;
}

ll get_fn(ll n) {
	mat a = mat_pow(A, n);
	return a.x[0][1];
}

int main() {
	cin >> n >> m >> p;
	ll fn2 = get_fn(n+2)-1;
	ll fm = get_fn(m);
	cout << fn2 % fm << endl;
	
	return 0;
} 
