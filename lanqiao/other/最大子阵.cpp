// 蓝桥杯 最大子阵
/*
	思路：
	利用前缀和
	每一列可以看作一个元素 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 510;

int n, m;
int nums[maxn][maxn];
int prefix[maxn][maxn];

void solve() {
	memset(prefix, 0, sizeof(prefix));
	for(int j = 1; j <= m; j++) {
		for(int i = 1; i <= n; i++) {
			prefix[i][j] = prefix[i-1][j] + nums[i][j];
		}
	}

	int ans = -INF;
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int sum = 0;
			for (int k = 1; k <= m; k++) {
				int num = prefix[j][k] - prefix[i-1][k];
				sum = (sum+num)<0 ? 0:(sum+num);
				if(sum > ans) ans = sum;
			}
		}
	}

	cout << (ans<0?0:ans) << endl;
}

int main() {
	scanf("%d%d", &n, &m);

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%d", &nums[i][j]);
		}
	}
	solve();

	return 0;
}
