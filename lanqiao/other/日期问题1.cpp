// 蓝桥杯 日期问题 
/*
	思路：
	枚举 
*/

#include <bits/stdc++.h>

using namespace std;

struct date {
	int y, m, d;
	date(int y_, int m_, int d_) {
		y = y_; m = m_; d = d_;
	}
	
	bool operator < (date node) const {
		if(y == node.y) {
			if(m == node.m) {
				return d < node.d;
			}
			return m < node.m;
		}
		return y < node.y;
	} 
};

int mon[13] = {0,31,30,31,30,31,30,31,31,30,31,30,31};
int a, b, c;
set<date> ans;

bool isRun(int y) {
	if(y%4==0 && y%100!=0) return true;
	if(y%400==0) return true;
	return false;
}

void putIn(int y, int m, int d) {
	if(y<1960 || y>2059) return;
	if(m<=0 || m>12) return;
	
	if(isRun(y)) {
		mon[2] = 29;
	} else {
		mon[2] = 28;
	}
	
	if(d<=0 || d>mon[m]) return;
	
	ans.insert(date(y, m, d));
}

void solve() {
	putIn(1900+a, b, c);
	putIn(2000+a, b, c);
	
	putIn(1900+c, a, b);
	putIn(2000+c, a, b);
	
	putIn(1900+c, b, a);
	putIn(2000+c, b, a);
	
	set<date>::iterator it;
	for(it = ans.begin(); it != ans.end(); it++) {
		printf("%02d-%02d-%02d\n", it->y, it->m, it->d);
	}
}

int main() {
	scanf("%d/%d/%d", &a, &b, &c);
	solve();
	
	return 0;
} 
