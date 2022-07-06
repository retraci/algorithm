// luogu_CF20C
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

#define INF 0x7fffffffffffffff
const int MAX_SIZE = 1e5+10;

typedef struct Node {
	int vex;
	long long w;

	bool operator > (const Node &rhs) const {
		return w > rhs.w;
	}
} Node;

typedef struct {
	vector<int> vexs[MAX_SIZE];
	vector<long long> arcs[MAX_SIZE];
} Graph;

Graph G;
long long dist[MAX_SIZE],parent[MAX_SIZE],ans[MAX_SIZE],m,n;
bool vis[MAX_SIZE];

void init() {
	// 初始化 dist数组
	for(int i=0; i<=n; i++) dist[i] = INF;
	memset(parent,-1,sizeof(parent));
	memset(vis,0,sizeof(vis));
}

void print() {
	int i = 0;
	for(int x=n; x!=-1; x=parent[x]) ans[i++] = x;
	int cnt = i;
	for(i=cnt-1; i>=0; i--) cout << ans[i] << " ";
}


void Dijkstra() {
	init();
	vis[1] = true;
	dist[1] = 0;
	for(int i=0; i<G.arcs[1].size(); i++) {
		int v = G.vexs[1][i];
		int w = G.arcs[1][i];
		if(dist[v]>w) {
			dist[v] = w;
			parent[v] = 1;
		}
	}
//	print();

	for(int k=0; k<n-1; k++) {		//取出 n-1个
		// 在 dist里找最小
		int minPos;
		long long min = INF;
		for(int i=1; i<=n; i++) {
			if(vis[i]) continue;
			if(min>dist[i]) {
				min = dist[i];
				minPos = i;
			}
		}
		vis[minPos] = true;

		// 将 v附近的节点加入 dist
		for(int i=0; i<G.vexs[minPos].size(); i++) {
			int v = G.vexs[minPos][i];
			long long w = G.arcs[minPos][i];
			if(dist[v]>w+min) {
				dist[v] = w+min;
				parent[v] = minPos;
			}
		}
//		print();
	}
}


void Dijkstra2() {
	priority_queue< Node,vector<Node>,greater<Node> > q;
	init();
	dist[1] = 0;
	Node n;
	n.vex = 1;
	n.w = 0;
	q.push(n);

	while(!q.empty()) {
		Node t = q.top();
		q.pop();
		int u = t.vex;
		long long min = dist[u];
		if(vis[u]) continue;
		vis[u] = true;

		for(int i=0; i<G.vexs[u].size(); i++) {
			int v = G.vexs[u][i];
			int w = G.arcs[u][i];
			if(dist[v]>w+min) {
				dist[v] = w+min;
				parent[v] = u;
				n.w = dist[v];
				n.vex = v;
				q.push(n);
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int a,b;
		long long w;
		cin >> a >> b >> w;
		G.vexs[a].push_back(b);
		G.vexs[b].push_back(a);
		G.arcs[a].push_back(w);
		G.arcs[b].push_back(w);
	}

	Dijkstra2();
//	for(int i=1;i<=n;i++) cout << dist[i] << " ";
	if(dist[n]==INF) cout << -1;
	else print();

	/*
	Node n1,n2,n0;
	n0.w = 0;
	n1.w = 1;
	n2.w = 2;
	priority_queue<Node> q;
	q.push(n1);
	q.push(n2);
	q.push(n0);
	cout << q.top().w;
	*/

	return 0;
}
