// 201712-4 行车路线
/*
	思路：
	把 que 当做状态，进行 Dijkstra 
	
	node:
	涉及平方运算，需要用到 long long  
	priority_queue 的 cmp 需要反转  
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Node {
	// type 在 graph 里充当类型
	// type 在 queue 里充当前一个状态（点）累计的小道长度 
	ll type, to, cost;
	Node(ll ty_, ll t_, ll c_) {
		type = ty_, to = t_, cost = c_;
	}
	bool operator < (Node n1) const {
		return cost > n1.cost;
	}
};

const int maxn = 510;

int n, m;
vector<Node> G[maxn];
int vis[maxn];
ll dist[maxn];

/*
5 4
1 1 2 2
1 2 3 2
0 3 4 2
1 4 5 2
*/

void Dijkstra(int s) {
	for(int i = 1; i <= n; i++) dist[i] = LONG_MAX;
	//memset(dist, LONG_MAX, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	priority_queue<Node> que;
	dist[s] = 0;
	que.push(Node(0, s, 0));
	
	while(!que.empty()) {
		Node n1 = que.top(); que.pop();
		int u = n1.to;
		if(vis[u]) continue;
		vis[u] = 1;
		//printf("%d %d\n", u, dist[u]);
		
		for(int i = 0; i < G[u].size(); i++) {
			Node &e = G[u][i];
			
			// 下一条路径类型为 0  
			if(e.type == 0) {
				if(dist[e.to] > 1ll*n1.cost+e.cost) {
					dist[e.to] = 1ll*n1.cost+e.cost;
					que.push(Node(0, e.to, dist[e.to]));
				}
				
			} else {
				// 前一个状态累计小道长度为 0  
				if(n1.type == 0) {
					if(dist[e.to] > 1ll*n1.cost+e.cost*e.cost) {
						dist[e.to] = 1ll*n1.cost+e.cost*e.cost;
						que.push(Node(e.cost, e.to, dist[e.to]));
					}
					
				// 前一个状态累计小道长度 >=0 
				} else {
					// 新累计小道长度 
					ll ndis = n1.type+e.cost;
					ll ncost = 1ll*n1.cost-n1.type*n1.type+ndis*ndis;
					if(dist[e.to] > ncost) {
						dist[e.to] = ncost;
						que.push(Node(ndis, e.to, dist[e.to]));
					}
				}
			}
		}
	}
}

void solve() {
	Dijkstra(1);
	cout << dist[n] << endl;
}

int main() {
	cin >> n >> m;
	int t, a, b, c;
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d%d", &t, &a, &b, &c);
		G[a].push_back(Node(t, b, c));
		G[b].push_back(Node(t, a, c));
	}
	solve();
	
	return 0;
}
