// 蓝桥杯11B 跑步训练
/*
	思路：
	模拟 
*/ 

#include <bits/stdc++.h>

using namespace std;

int main() {
	int t = 10000;
	int ans = 0;
	
	bool f = true; 
	while(true) {
		if(f) {
			for(int i = 0; i < 60; i++) {
				ans++;
				t -= 10;
				if(t == 0) {
					cout << ans << endl;
					exit(0);
				}
			}
			f = !f;
		} else {
			for(int i = 0; i < 60; i++) {
				ans++;
				t += 5;
				if(t == 0) {
					cout << ans << endl;
					exit(0);
				}
			}
			f = !f;
		}
	}
	cout << ans << endl;
	
	return 0;
}
