// POJ 3273 Monthly Expense
/*
	思路：
	二分答案
	
	node：
	ans 维护 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 100010;

int n, m;
int A[maxn];

int cal(int x) {
	int res = 1;
	int sum = 0;
	for(int i = 0; i < n; i++) {
		if(A[i] > x) return INF;
		
		sum += A[i];
		if(sum > x) {
			sum = A[i];
			res++;
		}
	}
	return res;
}

void solve() {
	int low = 0, high = INF;	
	
	int ans = 0;
	while(low <= high) {
		int mid = low + (high-low) / 2;
		if(cal(mid) > m) {
			low = mid + 1;
		} else {
			ans = mid;
			high = mid - 1;
		}
	}
	cout << ans << endl;
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	solve();
	
	return 0;
}
