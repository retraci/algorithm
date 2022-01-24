// 201703-5 引水入城 
/*
	思路：
	Dinic 
*/ 

#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Edge {
	ll to, next, w;
	Edge(ll t_, ll n_, ll w_) {
		to = t_, next = n_, w = w_;
	}
};

const ll maxn = 510;
const ll INF = 0x3f3f3f3f;

ll s, t;
ll n, m, A, B, Q, X;
vector<Edge> es;
ll head[maxn*maxn];
ll level[maxn*maxn];

ll get_rand() {
	return X=(A*X+B) % Q;
}

void add_edge(ll u, ll v, ll w) {
	es.push_back(Edge(v, head[u], w)); head[u] = es.size()-1;
	es.push_back(Edge(u, head[v], 0)); head[v] = es.size()-1;
}

bool bfs(ll s) {
	memset(level, 0, sizeof(level));
	queue<ll> que;
	level[s] = 1;
	que.push(s);
	
	while (!que.empty()) {
		int u = que.front(); que.pop();
		
		for (int i = head[u]; ~i; i=es[i].next) {
			int v = es[i].to;
			if (es[i].w && !level[v]) {
				level[v] = level[u] + 1;
				que.push(v);
			}
		}
	}
	
	return level[t];
}

ll dfs(ll u, ll f) {
	if (u == t || f == 0) return f;
	
	ll w, used = 0;
	for (int i=head[u]; ~i; i=es[i].next) {
		int v = es[i].to;
		if(es[i].w && level[v] == level[u]+1) {
			w = dfs(v, min(es[i].w, f-used));
			es[i].w -= w; es[i^1].w += w;
			used += w;
			if (used == f) return f; 
		}
	}
	
	if (!used) level[u] = -1;	
	return used;
}

void solve() {
	ll ans = 0;
	
	ll f;
	while(bfs(s)) {
		while((f=dfs(s, INF))) ans += f;
	}
	cout << ans << endl;
}

int main() {
	cin >> n >> m >> A >> B >> Q >> X;
	
	s = 0, t = n*m+1;
	memset(head, -1, sizeof(head));
	for(int i = 0; i < n-1; i++) {
		for(int j = 0; j < m; j++) {
			ll a = i*m+j+1;
			ll b = a + m;
			ll c = get_rand();
			add_edge(a, b, c);
			add_edge(b, a, INF);
		}
	}
	
	for(int i = 1; i < n-1; i++) {
		for(int j = 0; j < m-1; j++) {
			ll a = i*m+j+1;
			ll b = a + 1;
			ll c = get_rand();
			add_edge(a, b, c);
			add_edge(b, a, c);
		}
	}
	
	for(int j = 0; j < m; j++) {
		add_edge(s, j+1, INF);
	}
	
	for(int j = 0; j < m; j++) {
		ll a = (n-1)*m+j+1;
		add_edge(a, t, INF);
	}
		
	solve();
	
	return 0;
}
