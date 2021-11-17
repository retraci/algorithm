// POJ 1611 The Suspects
/*
	思路：
	并查集 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 30010;

int n, m;
int fa[maxn];

int find(int x) {
	return x==fa[x] ? x:fa[x]=find(fa[x]);
}

int main() {
	while(cin >> n >> m && n) {
		int ans = 1;
		for(int i = 0; i < n; i++) fa[i] = i;
		
		while(m--) {
			int cnt;
			cin >> cnt;
			
			int p, temp;
			scanf("%d", &p);
			cnt--;
			int tx = find(p);
			while(cnt--) {
				scanf("%d", &temp);
				
				int ty = find(temp);
				if(tx != ty) {
					fa[ty] = tx;
				}
			}
		}
		
		int tx = find(0);
		for(int i = 1; i < n; i++) {
			int ty = find(i);
			
			if(tx == ty) ans++;
		}
		
		cout << ans << endl;
	}
	
	return 0;
}
