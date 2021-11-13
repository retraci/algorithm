#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#define ll long long

const int N = 100010;

typedef pair<int, int> pii;

// 有向图 缩点
int n, m;
vector<pii> g[N];
int dfn[N], low[N], num;
stack<int> stk;
int in_stk[N];

int scc, c[N], sz[N];
vector<pii> gc[N];
int du[N];
int dist[N];

void add(int u, int v, int w) {
    g[u].push_back({v, w});
}

void tarjan(int u) {
    dfn[u] = low[u] = ++num;
    stk.push(u), in_stk[u] = 1;
    for (auto [v, w] : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        ++scc;
        int v;
        do {
            v = stk.top(); stk.pop();
            in_stk[v] = 0;
            c[v] = scc;
            sz[scc]++;
        } while (v != u);
    }
}

void add_c(int u, int v, int w) {
    gc[u].push_back({v, w});
    du[v]++;
}

void suodian() {
    for (int u = 1; u <= n; u++) {
        for (auto [v, w] : g[u]) {
            if (c[u] == c[v]) continue;
            add_c(c[u], c[v], w);
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    for (int u = 1; u <= n; u++) {
        for (auto &[v, w] : g[u]) {
            if (c[u] == c[v] && w != 0) {
                cout << -1 << endl;
                return;
            }
        }
    }

    suodian();
    queue<int> que;
    for (int i = 1; i <= scc; i++) {
        if (du[i] == 0) {
            dist[i] = 1;
            que.push(i);
        }
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (auto &[v, w] : gc[u]) {
            dist[v] = max(dist[v], dist[u] + w);
            if (--du[v] == 0) {
                que.push(v);
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= scc; i++) {
        ans += 1LL * dist[i] * sz[i];
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
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) add(a, b, 0), add(b, a, 0);
        else if (t == 2) add(a, b, 1);
        else if (t == 3) add(b, a, 0);
        else if (t == 4) add(b, a, 1);
        else add(a, b, 0);
    }
    solve();

    return 0;
}