// 201609-1 最大波动
/*
	思路：
	模拟 
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	int n;
	cin >> n;
	
	int last = 0;
	int ans = 0;
	for(int i = 0; i < n; i++) {
		if(i == 0) {
			cin >> last;
			continue;
		}
		int temp;
		cin >> temp;
		ans = max(ans, abs(temp-last));
		last = temp;
	}
	
	cout << ans << endl;
	
	return 0;
}
