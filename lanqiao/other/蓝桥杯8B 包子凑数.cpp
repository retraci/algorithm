// 蓝桥杯8B 包子凑数
/*
	思路：
	筛数 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6;

int n;
int A[110];
int vis[maxn];

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	
	vis[0] = 1;
	for(int i = 0; i < maxn; i++) {
		if(vis[i])
		for(int j = 0; j < n; j++) {
			if(i+A[j] < maxn)
				vis[i+A[j]] = 1;
		}
	}
	
	int ans = 0;
	for(int i = 1; i < maxn; i++) {
//		printf("%d %d\n", i, vis[i]);
		if(vis[i] == 0) ans++;
	}
	
	if(ans > 1e4) {
		cout << "INF" << endl;
	} else {
		cout << ans << endl;
	}
	
	return 0;
}

