#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const int N = 100010;

int n, m;
vector<int> g[N];
int dfn[N], low[N], num;
int cut[N];
ll sz[N], ans[N];

void add(int u, int v) {
    g[u].push_back(v);
}

void tarjan(int u, int pa) {
    dfn[u] = low[u] = ++num, sz[u] = 1;
    int cnt = 0, sum = 0;
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            sz[u] += sz[v];
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                cnt++;
                ans[u] += sz[v] * (n - sz[v]);
                sum += sz[v];

                if (pa != 0 || cnt >= 2) cut[u] = 1;
            }
        } else if (v != pa) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (cut[u]) {
        ll rem = n - (sum + 1);
        ans[u] += rem * (sum + 1) + (n - 1);
    } else {
        ans[u] = 2 * (n - 1);
    }
}

void solve() {
    memset(cut, 0, sizeof cut), memset(sz, 0, sizeof sz);
    num = 0;
    tarjan(1, 0);

    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }
    solve();

    return 0;
}