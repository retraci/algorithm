#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

/*----------------------------------------*/

// 无向图 割点
int n, m;
vector<int> g[N];

int dfn[N], low[N], num;
int cut[N];

void tarjan(int u, int fno) {
    dfn[u] = low[u] = ++num;
    int cnt = 0;
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);

            // 发现割点 u
            if (low[v] >= dfn[u]) {
                cnt++;
                if (fno != 0 || cnt >= 2) cut[u] = 1;
            }
        }

        // 遇到走过的, 证明 u 可以回到 v, 把 dfn[v] 维护到 low[u]
        if (dfn[v] != 0 && v != fno) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 无向图 割边
int n, m;
vector<int> g[N];

int dfn[N], low[N], num;
unordered_set<int> bs[N];

void tarjan(int u, int fno) {
    dfn[u] = low[u] = ++num;
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);

            // 发现割边 u -> v
            if (low[v] > dfn[u]) {
                bs[u].insert(v);
                bs[v].insert(u);
            }
        }

        // 遇到走过的, 证明 u 可以回到 v, 把 dfn[v] 维护到 low[u]
        if (dfn[v] != 0 && v != fno) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// e-dcc 缩点
int n, m;
vector<int> g[N];

int dcc, c[N], sz[N];
vector<int> gc[N];

void add_c(int u, int v) {
    gc[u].push_back(v);
}

void dfs_suodian(int u) {
    c[u] = dcc, sz[dcc]++;
    for (int v : g[u]) {
        if (c[v] || bs[u].count(v)) continue;
        dfs_suodian(v);
    }
}

void suodian() {
    dcc = 0;
    for (int i = 1; i <= n; i++) {
        if (!c[i]) {
            ++dcc;
            dfs_suodian(i);
        }
    }

    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (c[u] == c[v]) continue;
            add_c(c[u], c[v]), add_c(c[v], c[u]);
        }
    }
}
