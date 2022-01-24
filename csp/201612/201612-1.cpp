// 201612-1 中间数 
/*
	思路：
	map 计数 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, temp;
	map<int, int> mp;
	
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> temp;
		mp[temp]++;
	}
	
	int ans = -1;
	int l = 0, r = 0;
	for(int i = 1; i <= 1000; i++) {
		if(mp[i] == 0) continue;
		r = n - l - mp[i];
		if(l == r) {
			ans = i;
			break;
		}
		l += mp[i];
	}
	cout << ans << endl;
	
	return 0;
} 
