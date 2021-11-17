// POJ 3255 Roadblocks
/*
	次短路问题，单源最短路，且边均 e.cost>0 用 Dijkstra 即可
	加多一个 dist2 数组，保存次短路即可
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

struct Node {
	int to, cost;
	Node(int t_, int c_) {
		to = t_, cost = c_;
	}
	bool operator < (Node n1) const {
		return cost > n1.cost;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 5010;

int n, m;
vector<Node> G[maxn];
int dist1[maxn], dist2[maxn];

void Dijkstra(int s) {
	memset(dist1, INF, sizeof(dist1));
	memset(dist2, INF, sizeof(dist2));
	
	priority_queue<Node> que;
	// s -> s 不存在次短路 所以 dist2[s] = INF 
	dist1[s] = 0; 
	que.push(Node(s, 0));
	
	while(!que.empty()) {
		Node n1 = que.top(); que.pop();
		int u = n1.to;
		int dis_u = n1.cost;
		
		// 放宽条件 
		if(dis_u > dist2[u]) continue;
		
		for(int i = 0; i < G[u].size(); i++) {
			Node e = G[u][i];
			// 目前这个路径到 to 的距离 
			int temp = dis_u + e.cost;
			
			if(dist1[e.to] > temp) {
				swap(dist1[e.to], temp);
				// 加入最短路径 
				que.push(Node(e.to, dist1[e.to]));
			}
			
			// 添加条件，次短路必须大于最短路
			if(dist2[e.to] > temp && temp > dist1[e.to]) {
				swap(dist2[e.to], temp);
				// 加入可能的路径 
				que.push(Node(e.to, dist2[e.to]));
			}
		}
	}
}

void solve() {
	Dijkstra(1);
	
	cout << dist2[n] << endl;
}

int main() {
	int a, b, c;
	while(cin >> n >> m) {
		for(int i = 0; i <= n; i++) G[i].clear();

		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &c);
			G[a].push_back(Node(b, c));
			G[b].push_back(Node(a, c));
		}
		solve();
	}
	
	return 0;
}
