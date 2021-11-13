#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

const int N = 100010;

int n, m;
vector<int> g[N];
int dist[N];
int vis[N];
int fa[N];

void add(int u, int v) {
    g[u].push_back(v);
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void bfs(int s) {
    memset(vis, 0, sizeof vis);
    queue<pii> que;
    que.push({s, 0});
    vis[s] = 1;
    while (!que.empty()) {
        auto &[u, d] = que.front(); que.pop();
        dist[u] = d;

        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                que.push({v, d + 1});
            }
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        for (int v : g[i]) {
            int tx = find(i), ty = find(v);
            fa[tx] = ty;
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += i == find(i);
    if (cnt > 1) {
        cout << -1 << endl;
        return;
    }

    bfs(1);
    int id = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > mx) {
            mx = dist[i];
            id = i;
        }
    }

    bfs(id);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, dist[i]);
    cout << ceil(log2(ans)) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    solve();

    return 0;
}