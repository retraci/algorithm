// 蓝桥杯2014B 幂一矩阵 
/*
	思路：
	矩阵乘法 
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int maxn = 10000;

int n;
vector<vector<ll> > x;

bool check(vector<vector<ll> >& a) {
	for(int i = 0; i < n; i++) if(a[i][i] != 1) return false;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			if(a[i][j] != 0) return false;
		}
	}
	return true;
}

vector<vector<ll> > mult(vector<vector<ll> >& a, vector<vector<ll> >& b) {
	vector<vector<ll> > res = vector<vector<ll> >(n, vector<ll>(n, 0));
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				res[i][j] += a[i][k]*b[k][j];
			}
			
		}
	}
	
	return res;
}

void solve() {
	vector<vector<ll> > now = x;
	for(ll i = 2; i <= 1e18; i++) {
		now = mult(now, x);
		if(check(now)) {
			cout << i << endl;
			exit(0);
		}
	}
}

int main() {
	cin >> n;
	x = vector<vector<ll> >(n, vector<ll>(n, 0));
	
	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		x[a-1][b-1] = 1;
	}
	solve();
	
	return 0;
}
