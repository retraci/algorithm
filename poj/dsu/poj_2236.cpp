// POJ 2236 Wireless Network

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Node {
	int x, y;
};

const int maxn = 1010;

int n, d;
Node ns[maxn];
int fa[maxn];
int is_waked[maxn];

int get_dist2(int a, int b) {
	return (ns[a].x-ns[b].x)*(ns[a].x-ns[b].x) + (ns[a].y-ns[b].y)*(ns[a].y-ns[b].y);
}

int find(int x) {
	return x == fa[x] ? x: fa[x] = find(fa[x]);
}

void solve() {
	char ch;
	int a, b;
	for(int i = 0; i <= n; i++) fa[i] = i;
	
	while(cin >> ch) {
		if(ch == 'O') {
			scanf("%d", &a);
			is_waked[a] = 1;
			for(int i = 1; i <= n; i++) {
				if(a == i) continue;
				if(!is_waked[i]) continue;
				
				int dist = get_dist2(a, i);
				if(dist <= d*d) {
					int tx = find(a);
					int ty = find(i);
					if(tx != ty) {
						fa[tx] = ty;
					}
				}
			}
		} else if(ch == 'S') {
			scanf("%d%d", &a, &b);
			int tx = find(a);
			int ty = find(b);
			if(tx != ty) {
				printf("FAIL\n");
			} else {
				printf("SUCCESS\n");
			}
		}
	}
}

int main() {
	cin >> n >> d;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &ns[i].x, &ns[i].y);
	}
	solve();
	
	return 0;
}
