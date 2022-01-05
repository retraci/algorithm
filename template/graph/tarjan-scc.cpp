// region 有向图 缩点
int n, m;
vector<int> g[N];

int dfn[N], low[N], num;
stack<int> stk;
int in_stk[N];

int scc, c[N], sz[N];
vector<int> gc[N];

void tarjan(int u) {
    dfn[u] = low[u] = ++num;
    stk.push(u);
    in_stk[u] = 1;

    for (int v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }

        // 遇到走过的, 证明 u 可以回到 v, 把 dfn[v] 维护到 low[u]
        if (dfn[v] != 0 && in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        scc++;
        int v;
        do {
            v = stk.top(); stk.pop();
            in_stk[v] = 0;
            c[v] = scc;
            sz[scc]++;
        } while (v != u);
    }
}

void add_c(int u, int v) {
    gc[u].push_back(v);
}

void suodian() {
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (c[u] == c[v]) continue;
            add_c(c[u], c[v]);
        }
    }
}
// endregion