// 蓝桥杯 合根植物
/*
	思路：
	并查集 
*/ 

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int n, m;
int fa[MAXN*MAXN];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
	int a, b, k;
	cin >> n >> m >> k;
	for(int i = 0; i < n*m; i++) fa[i] = i;
	
	int ans = n*m;
	while(k--) {
		scanf("%d%d", &a, &b);
		int tx = find(a), ty = find(b);
		if(tx != ty) {
			ans--;
			fa[tx] = ty;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}

