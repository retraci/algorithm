// region scc 缩点
int e[M * 2], ne[M * 2], h1[N], h2[N], edm;

void add(int h[], int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int dfn[N], low[N], ti;
vector<int> stk;
int ins[N];
int co[N], sz[N], scc;

void tarjan(int u) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u), ins[u] = 1;

    for (int i = h1[u]; ~i; i = ne[i]) {
        int v = e[i];

        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        scc++;
        int t;
        do {
            t = stk.back(); stk.pop_back(); ins[t] = 0;
            co[t] = scc;
            sz[scc]++;
        } while (t != u);
    }
}
// endregion