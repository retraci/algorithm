// POJ 1182 食物链
/*
	思路：
	处理不同集合的并查集 
*/ 

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxn = 50010;

int n, k;
int fa[maxn*3];

int find(int x) {
	return x==fa[x] ? x : fa[x]=find(fa[x]);
}

void join(int a, int b) {
	int tx = find(a);
	int ty = find(b);
	if(tx != ty) 
		fa[tx] = ty;
}

int main() {
	cin >> n >> k;
	
	int ans = 0;
	int op, a, b;
	for(int i = 0; i <= 3*n; i++) fa[i] = i;
	while(k--) {
		scanf("%d%d%d", &op, &a, &b);
		
		// 条件 1 
		if(a > n || b > n) {
			ans++; continue;
		}
		
		if(op == 1) {
			int tx1 = find(a), tx2 = find(a+n);
			int ty1 = find(b), ty2 = find(b+n);
			
			if(tx1 == ty2 || ty1 == tx2) {
				ans++;
			} else {
				join(a, b);
				join(a+n, b+n);
				join(a+2*n, b+2*n);
			}
		} else {
			// 条件 2 
			if(a == b) {
				ans++; continue;
			}
			
			int tx1 = find(a), tx2 = find(a+n);
			int ty1 = find(b), ty2 = find(b+n);
			
			if(tx1 == ty1 || ty1 == tx2) {
				ans++;
			} else {
				join(a, b+n);
				join(a+n, b+2*n);
				join(a+2*n, b);
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
