// region 无边权的lca
int rt;
int dep[N], fa[N][32];

void lca_init() {
    memset(dep, -1, sizeof dep), memset(fa, 0, sizeof fa);

    queue<int> que;
    que.push(rt);
    dep[0] = 0, dep[rt] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto v = g[i];

            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u;
                que.push(v);

                for (int k = 1; k <= 31; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int k = 31; k >= 0; k--) {
        if (dep[fa[x][k]] >= dep[y]) x = fa[x][k];
    }
    if (x == y) return x;

    for (int k = 31; k >= 0; k--) {
        if (fa[x][k] != fa[y][k]) {
            x = fa[x][k], y = fa[y][k];
        }
    }
    return fa[x][0];
}
// endregion

// region 有边权的lca
int rt;
int dep[N], fa[N][32], w[N][32];

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void lca_init() {
    memset(dep, -1, sizeof dep), memset(fa, 0, sizeof fa), memset(w, 0x3f, sizeof w);

    queue<int> que;
    que.push(rt);
    dep[0] = 0, dep[rt] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u, w[v][0] = cost;
                que.push(v);

                for (int k = 1; k <= 31; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                    w[v][k] = w[v][k - 1] + w[fa[v][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int res = 0;
    for (int k = 31; k >= 0; k--) {
        if (dep[fa[x][k]] >= dep[y]) {
            res += w[x][k];
            x = fa[x][k];
        }
    }
    if (x == y) return res;

    for (int k = 31; k >= 0; k--) {
        if (fa[x][k] != fa[y][k]) {
            res += w[x][k] + w[y][k];
            x = fa[x][k], y = fa[y][k];
        }
    }
    res += w[x][0] + w[y][0];
    return res;
}
// endregion