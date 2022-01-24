// 最大化平均值 
/*
	求这个最大值 sum(vi)/sum(wi)
	
	思路： 
	二分法猜答案
	满足的条件 
	sum(vi)/sum(wi) >= x
	化简可得
	sum(vi-x*wi) >= 0 
	
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 1e4+10;

int n, k, w[maxn], v[maxn];
double a[maxn];

bool cmp(const double &a1, const double &a2) {
	return a1 > a2;
}

bool cal(double x) {
	double sum = 0;
	for(int i=0; i<n; i++) {
		a[i] = v[i] - x*w[i];
	}
	sort(a, a+n, cmp);
	
	for(int i=0; i<k; i++) {
		sum += a[i];
	}
	
	return sum >= 0;
}

void solve() {
	double lb = 0, ub = INF;
	for(int i=0; i<1000; i++) {
		double mid = (ub-lb)/2+lb;
		if(cal(mid)) lb = mid;
		else ub = mid;
	}
	
	printf("%.2lf", floor(lb*100)/100);
}

int main() {
	while(cin >> n >> k) {
		for(int i=0; i<n; i++) {
			scanf("%d", &w[i]);
		}
		for(int i=0; i<n; i++) {
			scanf("%d", &v[i]);
		}
		
		solve();
	}
		
	return 0;
} 
