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

void tarjan(int u, int pa) {
    dfn[u] = low[u] = ++num;
    int cnt = 0;
    for (int v : g[u]) {
        // 没走过
        if (!dfn[v]) {
            tarjan(v);
            // 把孩子的 low 更新到自己
            low[u] = min(low[u], low[v]);

            // 发现割点 u
            if (low[v] >= dfn[u]) {
                cnt++;
                if (pa != 0 || cnt >= 2) cut[u] = 1;
            }
        } else if (v != pa) {
            // 遇到走过的, 就把走过的 dfn 更新一下
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 无向图 割边
int n, m;
vector<int> g[N];
int dfn[N], low[N], num;
unordered_set<int> bridge[N];

void tarjan(int u, int pa) {
    dfn[u] = low[u] = ++num;
    for (int v : g[u]) {
        // 没走过
        if (!dfn[v]) {
            tarjan(v, u);
            // 把孩子的 low 更新到自己
            low[u] = min(low[u], low[v]);

            // 发现割边 u -> v
            if (low[v] > dfn[u]) {
                bridge[u].insert(v);
                bridge[v].insert(u);
            }
        } else if (v != pa) {
            // 遇到走过的, 就把走过的 dfn 更新一下
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
        if (c[v] || bridge[u].count(v)) continue;
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
