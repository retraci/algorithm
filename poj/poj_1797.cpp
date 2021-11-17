// POJ 1797 Heavy Transportation
// Dijkstra
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 0x7fffffff
using namespace std;

struct Node {
	int t,w;
	Node(int tt,int ww):t(tt),w(ww) {
	}

	bool operator < (const Node &temp) const {
		return w < temp.w;
	}
};

const int maxn = 1e3+10;
int n,m,maxw[maxn];
vector<Node> G[maxn];
bool vis[maxn];

void add(int f,int t,int w) {
	G[f].push_back(Node(t,w));
	G[t].push_back(Node(f,w));
}

void Dijkstra(int s) {
	priority_queue<Node> q;
	memset(vis,false,sizeof(vis));
	memset(maxw,0,sizeof(maxw));
	maxw[s] = INF;
	q.push(Node(s,maxw[s]));
	while(!q.empty()) {
		Node temp = q.top();
		q.pop();
		int u = temp.t;

		if(vis[u]) continue;
		vis[u] = true;

		int len = G[u].size();
		for(int i=0; i<len; i++) {
			int t = G[u][i].t;
			int w = G[u][i].w;
			int mu = maxw[u];
			int mt = maxw[t];

			if(mt<min(w,mu)) {
				maxw[t] = min(w,mu);
				q.push(Node(t,maxw[t]));
			}
		}
	}
}

int main() {
	int casee = 1;
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> m;
		for(int i=0;i<=n;i++) G[i].clear();
		for(int i=0; i<m; i++) {
			int f,t,w;
			cin >> f >> t >> w;
			add(f,t,w);
		}
		Dijkstra(1);

		printf("Scenario #%d:\n",casee++);
    	printf("%d\n\n",maxw[n]);
	}

	return 0;
}



