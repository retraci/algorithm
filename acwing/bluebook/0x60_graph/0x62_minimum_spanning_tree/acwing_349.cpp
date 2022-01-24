#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

typedef pair<int, int> pii;

const int N = 1010;
const ll MOD = (1LL << 31) - 1;

int n, m;
vector<pii> g[N];
int dist[N];
int vis[N];
int cnt[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

void dij(int s) {
    memset(dist, 0x3f, sizeof dist), memset(vis, 0, sizeof vis);
    dist[s] = 0;
    priority_queue<pii> que;
    que.push({0, s});
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop(); d = -d;
        if (vis[u]) continue;
        vis[u] = 1;

        for (auto &[v, w] : g[u]) {
            if (!vis[v] && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                que.push({-dist[v], v});
            }
        }
    }
}

void solve() {
    dij(1);

    ll ans = 1;
    memset(cnt, 0, sizeof cnt);
    for (int u = 1; u <= n; u++) {
        for (auto &[v, w] : g[u]) {
            if (dist[v] == dist[u] + w) cnt[v]++;
        }
    }
    for (int v = 1; v <= n; v++) {
        if (cnt[v]) ans = ans * cnt[v] % MOD;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    solve();

    return 0;
}