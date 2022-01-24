// 	集合竞价 - 201412-3
/*
	思路：
	答案一定在某个成交价，接着枚举即可 
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

struct data {
	double p;
	int s;
};

const int maxn = 5010;

int tot;
data buy[maxn], sell[maxn];
set<double> ps;

void init() {
	for(int i = 1; i <= tot; i++) {
		if(buy[i].s > 0) {
			ps.insert(buy[i].p);
		} else if(sell[i].s > 0) {
			ps.insert(sell[i].p);
		}
	}
}

long long cal_buy(double p) {
	long long res = 0;
	for(int i = 1; i <= tot; i++) {
		if(buy[i].s > 0 && buy[i].p >= p) {
			res += buy[i].s;
		}
	}
	return res;
}

long long cal_sell(double p) {
	long long res = 0;
	for(int i = 1; i <= tot; i++) {
		if(sell[i].s > 0 && sell[i].p <= p) {
			res += sell[i].s;
		}
	}
	return res;
}

void solve() {
	double p = 0;
	long long s = 0;
	init();
	for(set<double>::iterator it = ps.begin(); it != ps.end(); it++) {
		long long buy_num = cal_buy(*it);
		long long sell_num = cal_sell(*it);
		long long temp = buy_num > sell_num? sell_num : buy_num;
//		printf("%lf %d %d\n", ps[i], buy_num, sell_num);
		if(temp >= s) {
			s = temp;
			p = *it;
		}
	}
	printf("%.2f %lld\n", p, s);
}

int main() {
	string str;
	int t;
	while(cin >> str) {
		if(str == "buy") {
			tot++;
			scanf("%lf%d", &buy[tot].p, &buy[tot].s);
		} else if(str == "sell") {
			tot++;
			scanf("%lf%d", &sell[tot].p, &sell[tot].s);
		} else if(str == "cancel") {
			tot++;
			scanf("%d", &t);
			buy[t].s = 0;
			sell[t].s = 0;
		}
	}
//	for(int i = 1; i <= tot; i++) {
//		printf("%lf %d %lf %d\n", buy[i].p, buy[i].s, sell[i].p, sell[i].s);
//	}
	solve();

	return 0;
}
