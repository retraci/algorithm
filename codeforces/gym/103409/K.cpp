#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

typedef pair<ll, ll> pll;

const int N = 55;

int n, m;
ll vw[N * N];
vector<pll> g[N];
int vis[N];
ll dist[N];
ll cnt[N * N];
ll ans[N];

void add(int u, int v, int o) {
    g[u].push_back({v, o});
}

void bfs(int s) {
    for (int i = 1; i <= n; i++) dist[i] = 1e18, vis[i] = 0;

    queue<int> que;
    vis[s] = 1;
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (auto &[v, _] : g[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
}

void dfs(int u, ll cost) {
    for (auto &[v, ow] : g[u]) {
        if (dist[v] == dist[u] + 1) {
            cnt[ow]++;
            ans[v] = min(ans[v], cost + vw[ow] * cnt[ow]);
            dfs(v, cost + vw[ow] * cnt[ow]);
            cnt[ow]--;
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) cnt[i] = 0, ans[i] = 1e18;
    bfs(1);
    dfs(1, 0);

    for (int i = 2; i <= n; i++) {
        cout << ans[i] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> vw[i];
    for (int i = 1; i <= m; i++) {
        int u, v, ow;
        cin >> u >> v >> ow;
        add(u, v, ow), add(v, u, ow);
    }
    solve();

    return 0;
}