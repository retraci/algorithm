// 蓝桥杯 包子凑数
/*
	思路：
	如果这 n 个数的最大公约数不是 1，就说明有无穷多个数是凑不出来的
	欧拉筛素数
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 110;

int n, a[maxn];
int flag[maxn*maxn];

int gcd(int x, int y) {
	if(y == 0) return x;
	return gcd(y, x%y);
}

void solve() {
	int temp = a[0];
	for(int i = 1; i < n; i++) {
		temp = gcd(temp, a[i]);
	}
	if(temp != 1) {
		cout << "INF" << endl;
		return;
	}

	int maxx = maxn*maxn;
	for(int i = 0; i < n; i++) {
		for(int j = 1; j < maxx; j++) {
			if(flag[j] && j+a[i] < maxx) {
				flag[j+a[i]] = 1;
				continue;
			}
			if(j%a[i] == 0) {
				flag[j] = 1;
				continue;
			}
		}
	}

	int ans = 0;
	for(int j = 1; j < maxx; j++) {
		if(flag[j] == 0) ans++;
	}
	cout << ans << endl;
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	solve();

	return 0;
}
