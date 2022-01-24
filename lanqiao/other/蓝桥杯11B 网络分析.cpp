// 蓝桥杯11B 网络分析
/*
	思路：
	并查集
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 10010;

int n, m;
int fa[maxn];
int ans[maxn];

int find(int x) {
	return x==fa[x]? x: fa[x]=find(fa[x]);
}

int main() {
	int a, b, op;
	cin >> n >> m;
	
	for(int i = 0; i <= n; i++) fa[i] = i;
	while(m--) {
//		for(int i = 1; i <= n; i++) printf("%d ", fa[i]);
//		cout << endl;
		cin >> op >> a >> b;
		if(op == 1) {
			int tx = find(a);
			int ty = find(b);
			if(tx != ty)
				fa[tx] = ty;
		} else {
			int tx = find(a);
			int ty;
			for(int i = 1; i <= n; i++) {
				ty = find(i);
				if(tx == ty) {
					ans[i] += b;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		if(i < n) printf("%d ", ans[i]);
		else printf("%d\n", ans[i]);
	}

	return 0;
}
