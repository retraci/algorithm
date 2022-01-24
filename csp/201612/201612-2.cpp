// 201612-2 工资计算
/*
	思路：
	二分答案 
*/

#include <bits/stdc++.h>

using namespace std;

int n;

int cal(int x) {
	int T = x*100;
	int A = T-3500;
	int res = T;
	int a[10] = {0,1500,4500,9000,35000,55000,80000};
	
	if(A <= 0) return T;
	
	if(A >= a[1]) {
		res -= a[1] * 0.03;
		if(A >= a[2]) {
			res -= (a[2]-a[1]) * 0.1;
			if(A >= a[3]) {
				res -= (a[3]-a[2]) * 0.2;
				if(A >= a[4]) {
					res -= (a[4]-a[3]) * 0.25;
					if(A >= a[5]) {
						res -= (a[5]-a[4]) * 0.3;
						if(A >= a[6]) {
							res -= (a[6]-a[5]) * 0.35;
							res -= (A-a[6]) * 0.45;
						} else {
							res -= (A-a[5]) * 0.35;
						}
					} else {
						res -= (A-a[4]) * 0.3;
					}
				} else {
					res -= (A-a[3]) * 0.25;
				}
			} else {
				res -= (A-a[2]) * 0.2;
			}
		} else {
			res -= (A-a[1]) * 0.1;
		}
	} else {
		res -= A * 0.03;
	}
	
	return res;
}

void solve() {
	int low = 0, high = 1000;
	int ans = 0;

	while(low <= high) {
		int mid = (low+high) / 2;
		if(cal(mid) == n) {
			ans = mid*100;
			break;
		} else if(cal(mid) > n) {
			high = mid-1;
		} else {
			low = mid+1;
		}
	}
	cout << ans << endl;
}

int main() {
	cin >> n;
	solve();

	return 0;
}
