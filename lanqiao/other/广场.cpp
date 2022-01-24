// 广场 
/*

*/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m, a;
	cin >> n >> m >> a;
	
	long long x, y;
	if(n % a != 0) x = n/a+1;
	else x = n / a; 
	if(m % a != 0) y = m/a+1;
	else y = m / a;
	
	long long ans = x*y;
	
	cout << ans << endl;
	
	return 0;
} 
