// 线性分类器 202006-1/CCF

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const int maxn = 1010;

ll n, m;
ll x[maxn], y[maxn], ty[maxn];
ll a[25], b[25], c[25];

void solve() {
	ll k;
	bool ans;
	for (int i = 0; i < m; i++) {
		ans = true;
		k = 0; 
		for (int j = 0; j < n; j++) {
			ll temp = a[i]+b[i]*x[j]+c[i]*y[j] > 0 ? 1 : 0;
			
			if(ty[j] == 1) {
				if(k == 0) {
					k = temp;
				} else {
					if(temp != k) {
						ans = false;
						break;
					}
				}
			} else {
				if(k == 0) {
					k = !temp;
				} else {
					if(temp == k) {
						ans = false;
						break;
					}
				}
			}
		}
		if (ans) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}

int main() {
	cin >> n >> m;
	char ch;
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", &x[i], &y[i]);
		cin >> ch;
		if (ch == 'A') ty[i] = 1;
		else ty[i] = -1;
	}
	for (int i = 0; i < m; i++) {
		scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	}
	solve();

	return 0;
}
