// 递推求值

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const ll mod = 99999999;
const int ord = 7;

struct Mat {
	ll val[ord][ord];
	int n, m;
};

ll n;
Mat f;
Mat a, tmp;

void init() {
	a.n = a.m = ord;
	a.val[0][0] = 0, a.val[0][1] = 1, a.val[0][2] = 0, a.val[0][3] = 0, a.val[0][4] = 2, a.val[0][5] = 0, a.val[0][6] = 5;
	a.val[1][0] = 1, a.val[1][1] = 0, a.val[1][2] = 0, a.val[1][3] = 0, a.val[1][4] = 3, a.val[1][5] = 2, a.val[1][6] = 3;
	a.val[2][0] = 1, a.val[2][1] = 0, a.val[2][2] = 0, a.val[2][3] = 0, a.val[2][4] = 0, a.val[2][5] = 0, a.val[2][6] = 0;
	a.val[3][0] = 0, a.val[3][1] = 1, a.val[3][2] = 0, a.val[3][3] = 0, a.val[3][4] = 0, a.val[3][5] = 0, a.val[3][6] = 0;
	a.val[4][0] = 0, a.val[4][1] = 0, a.val[4][2] = 1, a.val[4][3] = 0, a.val[4][4] = 0, a.val[4][5] = 0, a.val[4][6] = 0;
	a.val[5][0] = 0, a.val[5][1] = 0, a.val[5][2] = 0, a.val[5][3] = 1, a.val[5][4] = 0, a.val[5][5] = 0, a.val[5][6] = 0;
	a.val[6][0] = 0, a.val[6][1] = 0, a.val[6][2] = 0, a.val[6][3] = 0, a.val[6][4] = 0, a.val[6][5] = 0, a.val[6][6] = 1;
	
	f.n = ord; f.m = 1;
	f.val[0][0] = 6;
	f.val[1][0] = 5;
	f.val[2][0] = 1;
	f.val[3][0] = 4;
	f.val[4][0] = 2;
	f.val[5][0] = 3;
	f.val[6][0] = 1;	
}

Mat muilt(Mat a, Mat b) {
	Mat res;
	res.n = a.n, res.m = b.m;
	
	for (int i = 0; i < res.n; i++) {
		for (int j = 0; j < res.m; j++) {
			res.val[i][j] = 0;
			for (int k = 0; k < a.m; k++) {
				res.val[i][j] = (res.val[i][j] + (a.val[i][k] * b.val[k][j]) % mod) % mod;
			}
		}
	}
	
	return res;
}

Mat qpow(Mat a, ll b) {
	Mat res = a;
	b--;
	while (b) {
		if (b & 1) {
			res = muilt(res, a);
		}
		a = muilt(a, a);
		b >>= 1;
	}
	
	return res;
}

void solve() {
	init();
	
	ll ans1, ans2;
	if (n == 3) {
		ans1 = f.val[0][0], ans2 = f.val[1][0];
	} else if (n == 2) {
		ans1 = f.val[2][0], ans2 = f.val[3][0];
	} else if (n == 1) {
		ans1 = f.val[4][0], ans2 = f.val[5][0];
	} else {
		Mat res = qpow(a, n-3);
		f = muilt(res, f);
		ans1 = f.val[0][0], ans2 = f.val[1][0];
	}
	
	printf("%d\n%d\n", ans1, ans2);	
}

int main() {
	cin >> n;
	solve();
	
	return 0;
}
