// region 无边权的lca
int dep[N], fa[N][32];

void lca_init(int rt) {
    fill(dep, dep + n + 1, -1);

    queue<int> que;
    que.push(rt);
    dep[0] = 0, dep[rt] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = g[i];

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
int dep[N], fa[N][32];
ll w[N][32];

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void lca_init(int rt) {
    fill(dep, dep + n + 1, -1);

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

ll lca(int x, int y) {
    ll res = 0;
    if (dep[x] < dep[y]) swap(x, y);
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

// region 无边权的欧拉序lca
int id[N], eula[2 * N], cnt;
int dep[2 * N], st[2 * N][32], lg[2 * N];

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
// endregion
