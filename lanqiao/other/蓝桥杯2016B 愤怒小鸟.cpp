// 蓝桥杯2016B 愤怒小鸟 
/*
	思路：
	模拟 
*/

#include <bits/stdc++.h>

using namespace std;

void btoa(double a, double b);

double va = 10, vb = 10, vx = 50;
int ans;

void atob(double a, double b) {
	if(b-a <= 1) {
		cout << ans << endl;
		return;
	}
	
	double time = (b-a) / (vx+vb);
	ans++;
	double nb = b-vb*time;
	double na = a+va*time;
	btoa(na, nb);
}

void btoa(double a, double b) {
	if(b-a < 1) {
		cout << ans-1 << endl;
		return;
	} else if(b-a == 1) {
		cout << ans << endl;
		return;
	}
	
	double time = (b-a) / (vx+vb);
	double nb = b-vb*time;
	double na = a+va*time;
	atob(na, nb);
}

int main() {
	atob(0, 1000);
	
	return 0;
} 
