// POJ 3579 Median

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 10;

int n, m;
int va[maxn];

bool check(int mid) {	
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt += va+n - lower_bound(va+i+1, va+n, va[i]+mid);
	}
	
	return cnt > m/2;
}

void solve() {
	m = 1LL*n*(n-1) / 2;
	sort(va, va+n);
	
	int left = 0, right = va[n-1]-va[0];
	while (left < right) {
		int mid = (left + right + 1) >> 1;
		if (check(mid)) left = mid;
		else right = mid - 1;
	}
	
	printf("%d\n", left);
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &va[i]);
		}
		solve();
	}
	
	return 0;
}
