// 201912-1
/*

*/

#include <bits/stdc++.h>

using namespace std;

int a[4];

bool check(int x) {
	if((x%7) == 0) return true;
	
	while(x) {
		if((x % 10) == 7) return true;
		x /= 10;
	}
	return false;
}

int main() {
	int n;
	cin >> n;
	
	int now = 0;
	for(int i = 0; i < n; i++) {
		if(check(now+1)) {
			//cout << now+1 << endl;
			i--;
			a[now%4]++;
		}
		now++;
	}

	for(int i = 0; i < 4; i++) printf("%d\n", a[i]);
	
	return 0;
}
