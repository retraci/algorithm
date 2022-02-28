// region v-dcc
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
// endregion

// region e-dcc
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
// endregion
