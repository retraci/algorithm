// POJ 1862 Stripies
/*
	思路：
	贪心，选最大的两个合并
	原因，大的数字开次方次数越多，数字越小
*/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
//	int n;
//	vector<double> v;
//	cin >> n;
//	v.clear();
//	int temp;
//	for(int i = 0; i < n; i++) {
//		scanf("%d", &temp);
//		v.push_back(temp);
//	}
//	sort(v.begin(), v.end());
//
//	double ans = v[n-1];
//	for(int i = n-2; i >= 0; i--) {
//		ans = 2*sqrt(ans*v[i]);
//	}
//
//	printf("%.3llf\n", ans);
//
//	return 0;
	int n;
	vector<double> v;
	cin >> n;

	int temp;
	for(int i = 0; i < n; i++) {
		scanf("%d", &temp);
		v.push_back(temp);
	}
	sort(v.begin(), v.end());

	while(v.size() > 1) {
		double t1 = v.back();
		v.pop_back();
		double t2 = v.back();
		v.pop_back();
		double t = 2*sqrt(t1*t2);
		v.push_back(t);
	}
	printf("%.3f", v[0]);

	return 0;
}
