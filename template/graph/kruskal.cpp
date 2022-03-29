// region kruskal重构树
int n, m;
ti3 es[M];

int h[2 * N], ne[2 * N], g[2 * N], edm;
int pa[2 * N], w[2 * N], tt;

int id[2 * N], eula[4 * N], dep[4 * N], cnt;
int st[4 * N][23], lg[4 * N];

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

bool unite(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return false;
    pa[tx] = ty;
    return true;
}

void add(int u, int v) {
    g[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u) {
    eula[++cnt] = u, id[u] = cnt;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];

        dep[v] = dep[u] + 1;
        dfs(v);
        eula[++cnt] = u;
    }
}

void init_st(int rt) {
    dep[rt] = 1;
    dfs(tt);

    lg[0] = -1;
    for (int i = 1; i <= cnt; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= cnt; i++) st[i][0] = eula[i];
    for (int k = 1; (1 << k) <= cnt; k++) {
        for (int i = 1; i + (1 << k) - 1 <= cnt; i++) {
            int a = st[i][k - 1];
            int b = st[i + (1 << (k - 1))][k - 1];

            st[i][k] = dep[a] < dep[b] ? a : b;
        }
    }
}

int lca(int x, int y) {
    int L = id[x], R = id[y];
    if (L > R) swap(L, R);

    int k = lg[R - L + 1];
    int a = st[L][k];
    int b = st[R - (1 << k) + 1][k];

    return dep[a] < dep[b] ? a : b;
}

void init() {
    sort(es + 1, es + m + 1, [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });
    iota(pa, pa + 2 * n + 1, 0);
    fill(h, h + 2 * n + 1, -1), edm = 0;
    tt = n;
    for (int i = 1; i <= m; i++) {
        auto[u, v, cost] = es[i];
        int tu = find(u), tv = find(v);
        if (tu == tv) continue;

        tt++;
        unite(tu, tt), unite(tv, tt);
        add(tt, tu), add(tt, tv);
        w[tt] = cost;
    }

    init_st(tt);
}
// endregion
