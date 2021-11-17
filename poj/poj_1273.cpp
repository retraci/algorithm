// POJ 1273 Drainage Ditches
/*
	思路：
	Dinic 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Node {
	int to, cap, rev;
	Node(int t_, int c_, int r_) {
		to = t_, cap = c_, rev = r_;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 210;

int n, m, s, t;
vector<Node> G[maxn];
int level[maxn];
int iter[maxn];

void add_edge(int from, int to, int cap) {
	G[from].push_back(Node(to, cap, G[to].size()));
	G[to].push_back(Node(from, 0, G[from].size()-1));
}

void bfs(int s) {
	for(int i = 0; i <= n; i++) level[i] = INF;
	level[s] = 0;
	queue<int> que;
	que.push(s);
	
	while(!que.empty()) {
		int u = que.front(); que.pop();
		for(int i = 0; i < G[u].size(); i++) {
			Node &e = G[u][i];
			if(e.cap > 0 && level[e.to]>level[u]+1) {
				level[e.to] = level[u] + 1;
				que.push(e.to);
			}
		}
	}
}

// 到达 x 时候的最大流为 mf 
int dfs(int x, int t, int mf) {
	if(x == t) return mf;
	
	for(int &i=iter[x]; i < G[x].size(); i++) {
		Node &e = G[x][i];
		if(e.cap > 0 && level[e.to] > level[x]) {
			// 往下一个点找	增广路 
			int delta = dfs(e.to, t, min(mf, e.cap));
			// 如果找到了 维护一下 e.cap 与 G[to][from].cap 
			if(delta > 0) {
				e.cap -= delta;
				G[e.to][e.rev].cap += delta;
				return delta;
			}
		}
	}
	
	// 找不到 
	return 0;
}

void solve() {
	s = 1; t = n;
	int ans = 0;
	while(1) {
		bfs(s);
		if(level[t] == INF) break;
			
		memset(iter, 0, sizeof(iter));
		int f;
		while((f=dfs(s, t, INF)) > 0) {
			ans += f;
		}
	}
	cout << ans << endl;
}

int main() {
	int a, b, c;
	while(cin >> m >> n) {
		for(int i = 0; i <= n; i++) G[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &c);
			add_edge(a, b, c);
		}
		solve();
	}	
	
	return 0;
}
