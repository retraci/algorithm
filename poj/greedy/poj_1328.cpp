// POJ 1328 Radar Installation
/*
	思路：贪心
	每个岛对应一个区间
	定义一个右边界，如果岛的区间的左边界大于有边界，那么 ans+1 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

struct range {
	double left, right;
};

const int maxn = 1010;

int n, d;
range island[maxn];

bool cmp(const range &r1, const range &r2) {
	if(r1.right == r2.right) return r1.left > r2.left;
	else return r1.right < r2.right;
}

int solve() {
	int res = 1;
	sort(island, island+n, cmp);
	// maxr之前的均已经覆盖 
	double maxr = island[0].right;
	
	for(int i = 1; i < n; i++) {
		// 当 i 不能被覆盖时 
		if(island[i].left > maxr) {
			// 在 i 的右侧建立雷达 
			maxr = island[i].right;
			res++;
		}
	}
	
	return res;
}

int main() {
	int T = 0;
	while(~scanf("%d%d", &n, &d) && n && d) {
		int x, y;
		int flag = 0;
		if(d < 0) flag = 1;
		for(int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			if(y > d) flag = 1;
			double del = sqrt(d*d-y*y);
			island[i].left = x-del;
			island[i].right = x+del;
		}
		int ans = -1;
		if(!flag) ans = solve();
		printf("Case %d: %d\n", ++T, ans);
	}
	
	return 0;
}
