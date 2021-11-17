// POJ 2976 Dropping tests
/*
	思路：
	01分数规划 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

const int maxn = 1010;
const double eps = 1e-6;

int n, m;
double va[maxn], vb[maxn], vv[maxn];

bool check(double mid) {
	for (int i = 0; i < n; i++) {
		vv[i] = va[i] - mid * vb[i];
	}
	sort(vv, vv+n, greater<double>());
	double res = 0;
	for (int i = 0; i < n-m; i++) {
		res += vv[i];
	}

	return res >= 0;
}

void solve() {
	double left = 0, right = 1;
	while (right - left > eps) {
		double mid = (left + right) / 2;
		if (check(mid)) left = mid;
		else right = mid;
	}
	
	printf("%.0lf\n", left*100);
}

int main() {
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		for (int i = 0; i < n; i++) scanf("%lf", &va[i]);
		for (int i = 0; i < n; i++) scanf("%lf", &vb[i]);
		solve();
	}
	
	return 0;
}
