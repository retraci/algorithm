#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 100010;

typedef pair<int, int> pii;

int n, K;
vector<pii> g[N];
int vis[N];
int pre[N];
int d1, d2;
int f[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

int bfs(int s) {
    memset(vis, 0, sizeof vis);
    queue<int> que;
    que.push(s);
    int t = s;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        if (vis[u]) continue;
        t = u;
        vis[u] = 1;

        for (auto &[v, w] : g[u]) {
            if (!vis[v]) {
                pre[v] = u;
                que.push(v);
            }
        }
    }
    return t;
}

int get_len(int s, int t) {
    int res = 0;
    int v = t;
    while (v != s) {
        res++;
        v = pre[v];
    }
    return res;
}

void dfs(int u) {
    vis[u] = 1;
    for (auto &[v, w] : g[u]) {
        if (vis[v]) continue;

        dfs(v);
        d2 = max(d2, f[u] + f[v] + w);
        f[u] = max(f[u], f[v] + w);
    }
}

void work(int s, int t) {
    int v = t;
    while (v != s) {
        int u = pre[v];
        for (auto &[tv, w] : g[u]) {
            if (tv == v) w = -1;
        }
        for (auto &[tu, w] : g[v]) {
            if (tu == u) w = -1;
        }
        v = u;
    }

    memset(vis, 0, sizeof vis);
    dfs(1);
}

void solve() {
    int s = bfs(1);
    int t = bfs(s);
    d1 = get_len(s, t);

    if (K == 1) {
        cout << 2 * (n - 1) - (d1 - 1) << endl;
    } else {
        work(s, t);
        cout << 2 * (n - 1) - (d1 - 1) - (d2 - 1) << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v, 1), add(v, u, 1);
    }
    solve();

    return 0;
}