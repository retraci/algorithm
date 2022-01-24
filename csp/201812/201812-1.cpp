// 201812-1
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int r, y, g;
	int n;
	cin >> r >> y >> g >> n;
	
	int ans = 0;
	int temp1, temp2;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &temp1, &temp2);
		if(temp1 == 0) {
			ans += temp2;
		} else if(temp1 == 1) {
			ans += temp2;
		} else if(temp1 == 2) {
			ans += temp2 + r;
		} else if(temp1 == 3) {
			continue;
		}
	}
	cout << ans << endl;
		
	return 0;
}
