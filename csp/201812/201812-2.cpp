// 201812-2
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

int n;
long long a[3];
long long T;
long long ans;

long long getTime(int t, int light, long long now) {
	long long time = ans;
	while(time >= T) time -= T;
	
	while(time >= 0) {
		if(time < now) {
			if(light == 1) return 0;
			else if(light == 2) return a[0] + now - time;
			else return now - time;
		}
		time -= now;
		
		light = (light+1) % 3;
		now = a[light];
	}
	
}

int main() {
	cin >> a[0] >> a[2] >> a[1] >> n;
	T = a[0] + a[1] + a[2];
	
	long long temp1, temp2;
	for(int i = 0; i < n; i++) {
		scanf("%I64d%I64d", &temp1, &temp2);
		if(temp1 == 0) {
			ans += temp2;
		} else {
			if(temp1 == 1) temp1 = 0;
			else if(temp1 == 2) temp1 = 2; 
			else if(temp1 == 3) temp1 = 1;
			ans += getTime(ans, temp1, temp2);
		}
	}
	cout << ans << endl;
	
	return 0;
}
