// POJ 3104 Drying
/*
	思路：
	二分答案

	node：
	ans 维护
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 100010;

int n, k;
int A[maxn];
int low, high;

bool check(int x) {
	int sum = 0;

	for(int i = 0; i < n; i++) {
		if(A[i] > x) {
			double temp = 1.0*(A[i]-x) / (k-1);
			sum += ceil(temp);

			if(sum > x) return false;
		}
	}

	return true;
}

void solve() {
	if(k == 1) {
		cout << high << endl;
		return;
	}

	int ans = high;
	while(low <= high) {
		int mid = low + (high-low) / 2;
		if(check(mid)) {
			ans = mid;
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	cout << ans << endl;
}

int main() {
	while(cin >> n) {
		low = high = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
			high = max(high, A[i]);
		}
		cin >> k;
		solve();
	}

	return 0;
}
