// 201809-5
/*
	
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll MOD = 998244353;
const int maxn = 1e5+10;

ll a[maxn];
ll k[maxn];

int main() {
	int m, l, r;
	cin >> m >> l >> r;
	for(int i = 1; i <= m; i++) {
		scanf("%I64d", &k[i]);
	}
	a[0] = 1;
	for(int i = 1; i <= r; i++) {
		for(int j = 1; j <= i; j++) {
			a[i] = (a[i] + k[j]*a[i-j]) % MOD;
		}
		if(i >= l) cout << a[i] << endl;
	}
	
	return 0;
} 
