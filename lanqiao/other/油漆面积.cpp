// 蓝桥杯 油漆面积 
/*
	思路：
	模拟 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1e4+10;

int n;
bool mp[maxn][maxn];

int main() {
	cin >> n;
	int x1, x2, y1, y2;
	int ans = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		int minx = min(x1, x2), maxx = max(x1, x2);
		int miny = min(y1, y2), maxy = max(y1, y2);
		for(int j = minx; j < maxx; j++) {
			for(int k = miny; k < maxy; k++) {
				if(!mp[j][k]) {
					ans++;
					mp[j][k] = true;
				}
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
} 
