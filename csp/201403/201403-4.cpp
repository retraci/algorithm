// 无线网络 - 201403-4
/*	
	思路：
	建图 + bfs 
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

#define ll long long

struct point {
	ll x, y;
};

struct vec {
	int v, used, cost;
};

const int maxn = 220;

ll n, m, k, r;
int N, ans;
vector<int> G[maxn];
point ps[maxn];
bool vis[maxn];
int sum[maxn];

bool is_connected (point p1, point p2) {
	ll dis1 = (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y);
	ll dis2 = r * r;
	if(dis1 <= dis2) return true;
	else return false;
}

void bfs() {
	memset(vis, false, sizeof(vis));
	vis[1] = true;
	queue<vec> que;
	que.push(vec {1, 0, 0});

	while(!que.empty()) {
		vec ve1 = que.front();
		que.pop();
		int v = ve1.v;
		if(v == 2) {
			ans = ve1.cost-1;
			break;
		}

		for(int i = 0; i < G[v].size(); i++) {
			int u = G[v][i];			
			if(u <= n) {
				if(vis[u] && ve1.used >= sum[u]) continue;
				sum[u] = ve1.used;
				vis[u] = true;
//				printf("\n%d %d", v, u);
				que.push(vec {u, ve1.used, ve1.cost+1});
			} else if(ve1.used < k) {
				if(vis[u] && ve1.used+1 >= sum[u]) continue;
				sum[u] = ve1.used+1;
				vis[u] = true;
//				printf("\n%d %d", v, u);
				que.push(vec {u, ve1.used+1, ve1.cost+1});
			}
		}
	}
}

void solve() {
	for(int i = 1; i <= N; i++) {
		for(int j = i+1; j <= N; j++) {
			if(is_connected(ps[i], ps[j])) {
				G[i].push_back(j);
				G[j].push_back(i);
			}
		}
	}
	bfs();
//	for(int i = 1; i <= N; i++) printf("%d ", sum[i]);
	cout << ans << endl;
}

int main() {
	scanf("%I64d%I64d%I64d%I64d", &n, &m, &k, &r);
	N = n+m;
	for(int i = 1; i <= n; i++) {
		scanf("%I64d%I64d", &ps[i].x, &ps[i].y);
	}
	for(int i = n+i; i <= n+m; i++) {
		scanf("%I64d%I64d", &ps[i].x, &ps[i].y);
	}
	solve();

	return 0;
}
