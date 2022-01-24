// 蓝桥杯 日期问题 
/*
	思路：
	模拟 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

struct node {
	int year, month, day;

	bool operator < (node b) const {
		if (year == b.year) {
			if (month == b.month) {
				return day < b.day;
			}
			return month < b.month;
		}
		return year < b.year;
	}
};

int a, b, c;
int y, m, d;
int mon[13] = {0,31,30,31,30,31,30,31,31,30,31,30,31};
set<node> v;

bool is_run(int x) {
	if(x%4 == 0 && x%100 != 0) return true;
	if(x%400 == 0) return true;
	return false;
}

bool judge() {
	if(y < 1960 || y > 2059) return false;
	if(m < 0 || m > 12) return false;
	if(is_run(y)) mon[2] = 29;
	else mon[2] = 28;
	if(d < 1 || d > mon[m]) {
		return false;
	}
	return true;
}

void insert(int year, int month, int day) {
	y = year;
	m = month;
	d = day;
	if(judge()) {
		node n1;
		n1.year = y;
		n1.month = m;
		n1.day = d;
		v.insert(n1);
	}
}

void solve() {
	insert(1900+a, b, c);
	insert(2000+a, b, c);

	insert(1900+c, a, b);
	insert(2000+c, a, b);

	insert(1900+c, b, a);
	insert(2000+c, b, a);

	set<node>::iterator it = v.begin();
	for(; it!=v.end(); it++) {
		printf("%d-%02d-%02d\n", it->year, it->month, it->day);
	}
}

int main() {
	scanf("%d/%d/%d", &a, &b, &c);
	solve();

	return 0;
}
