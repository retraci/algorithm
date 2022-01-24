// 201703-1 分蛋糕 
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	
	int temp;
	int cur = 0;
	int ans = 0;
	while(n--) {
		cin >> temp;
		cur += temp;
		if(cur >= k) {
			ans++;
			cur = 0;
		}
	}
	if(cur > 0) ans++;
	cout << ans << endl;
	
	return 0;
}
