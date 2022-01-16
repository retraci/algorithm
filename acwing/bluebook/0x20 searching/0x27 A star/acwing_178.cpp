#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 1010;

struct Node {
    int w, d, u;
    bool operator<(const Node &rhs) const {
        return w > rhs.w;
    }
};

int n, m;
vector<pii> g[N], rg[N];
int s, t, K;

int dist[N];
int vis[N];

void add(int u, int v, int cost) {
    g[u].push_back({v, cost});
}

void radd(int u, int v, int cost) {
    rg[u].push_back({v, cost});
}

void dij() {
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);

    priority_queue<pii> que;
    dist[t] = 0;
    que.push({0, t});
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop(); d = -d;
        if (vis[u]) continue;
        vis[u] = 1;

        for (auto &[v, cost] : rg[u]) {
            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push({-dist[v], v});
            }
        }
    }
}

int A_star() {
    memset(vis, 0, sizeof vis);

    priority_queue<Node> que;
    que.push({dist[s], 0, s});
    while (!que.empty()) {
        auto [w, d, u] = que.top(); que.pop();
        if (++vis[u] > K) continue;
        if (vis[t] == K) return d;

        for (auto &[v, cost] : g[u]) {
            int nd = d + cost;
            int y = nd + dist[v];
            if (vis[v] < K) que.push({y, nd, v});
        }
    }

    return -1;
}

void solve() {
    dij();

    if (dist[s] == -1) {
        cout << -1 << "\n";
        return;
    }
    if (s == t) K++;
    cout << A_star() << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        add(u, v, cost), radd(v, u, cost);
    }
    cin >> s >> t >> K;
    solve();

    return 0;
}