// POJ 3621 Sightseeing Cows
/*
	思路：
	01 分数规划 
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f;
#define eps 1e-5

const int maxn = 1010;

struct Node {
	int to;
	double cost;
	Node(int v, double c) {
		to = v; cost = c;
	}
};

int n, m;
double va[maxn];
vector<Node> g[maxn];
double dist[maxn];
int inQue[maxn];
int cnt[maxn];

void addEdge(int u, int v, int c) {
	g[u].push_back(Node(v, c));
}

double calc(int u, int i, double mid) {
	int v = g[u][i].to;
	return g[u][i].cost * mid - va[v];
}

bool spfa(int s, double mid) {
	queue<int> que;
	for (int i = 0; i < n; i++) dist[i] = INF;
	memset(inQue, 0, sizeof(inQue));
	memset(cnt, 0, sizeof(cnt));
	
	dist[0] = 0;
	que.push(0);
	inQue[0] = 1;
	cnt[0]++;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		inQue[u] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			Node &e = g[u][i];
			int v = e.to;
			double cost = calc(u, i, mid);
			if (dist[v] > dist[u] + cost) {
				dist[v] = dist[u] + cost;

				if (!inQue[v]) {
					que.push(v);
					inQue[v] = 1;
					if (++cnt[v] >= n) return false;
				}				
			}
		}
	}
	
	return true;
}

bool check(double mid) {
	return spfa(0, mid);
}
 
void solve() {
	double left = 0, right = 1e9;
	while (right - left > eps) {
		double mid = (left + right) / 2;
		if (check(mid)) right = mid;
		else left = mid;
	}
	
	printf("%.2lf", right);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		scanf("%lf", &va[i]);
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		double c;
		scanf("%d%d%lf", &u, &v, &c);
		addEdge(u-1, v-1, c);
	}
	solve();
	
	return 0;
}
