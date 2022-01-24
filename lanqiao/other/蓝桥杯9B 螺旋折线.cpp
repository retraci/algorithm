// 蓝桥杯9B 螺旋折线
/*
	思路：
	找规律 
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
	ll x, y;
	cin >> x >> y;
	
	ll ans;
	if(x >= 0 && y >= 0) {			// 第一象限
		ll d = max(x, y);
		if(x >= y) {
			ans = 4*d*d+(d-y);
		} else {
			ans = 4*d*d-(d-x);
		}
	} else if(x <= 0 && y <= 0) {	// 第三象限 
		x = abs(x); y = abs(y);
		ll d = max(x, y);
		if(x-(y+1) >= 0) {
			ans = (2*d-1)*(2*d-1)+(d-(y+1));
		} else {
			ans = (2*d-1)*(2*d-1)-(d-x);
		}
	} else if(x >= 0 && y <= 0) {	// 第四象限 
		x = abs(x); y = abs(y);
		ll d = max(x, y);
		if(x >= y) {
			ans = (4*d*d+2*d)-(d-y);
		} else {
			ans = (4*d*d+2*d)+(d-x);
		}
	} else if(x <= 0 && y >= 0) { 	// 第二象限 
		x = abs(x); y = abs(y);
		ll d = max(x, y);
		if(x >= y) {
			ans = (4*d*d-2*d)-(d-y);
		} else {
			ans = (4*d*d-2*d)+(d-x);
		}
	}
	
	cout << ans << endl;
	
	return 0;
} 
