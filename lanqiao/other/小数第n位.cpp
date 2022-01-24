// 蓝桥杯 小数第n位 
/*
	思路：
	数论
	
	  (a/b * 10^(n+2) ) % MOD
	= a*10^(n+2) % (MOD*b) / b
	= a % (MOD*b) * 10^(n+2) % (MOD*b) / b
	
	node:
	x/d % m = x % (d*m) / d 
*/ 

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const LL MOD = 1e3;

LL a, b, n;

LL q_pow(LL a, LL b, LL mod) {
	LL res = 1, base = a;
	while(b) {
		if(b & 1) res = (res*base) % mod;
		base = (base * base) % mod;
		b >>= 1;
	}
	return res;
}

void solve() {
	LL mod = MOD * b;
	LL ans = (a % mod * q_pow(10, n+2, mod) % mod) / b;
	cout << ans << endl;
}

int main() {
	cin >> a >> b >> n;
	solve();
	
	return 0;
} 
