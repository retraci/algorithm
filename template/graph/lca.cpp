// region 无权的lca
template<int N, int M>
struct Lca {
    int n, mxb;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;
    int dep[N + 10], fa[N + 10][32];

    Lca() {}

    void init(int _n) {
        n = _n, mxb = __lg(n);
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void init_lca(int rt) {
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1;
        while (!que.empty()) {
            auto u = que.front(); que.pop();

            for (int i = h[u]; ~i; i = ne[i]) {
                int v = e[i];

                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    fa[v][0] = u;
                    que.push(v);

                    for (int k = 1; k <= mxb; k++) {
                        fa[v][k] = fa[fa[v][k - 1]][k - 1];
                    }
                }
            }
        }
    }

    int work(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[x][k]] >= dep[y]) x = fa[x][k];
        }
        if (x == y) return x;

        for (int k = mxb; k >= 0; k--) {
            if (fa[x][k] != fa[y][k]) {
                x = fa[x][k], y = fa[y][k];
            }
        }
        return fa[x][0];
    }
};
// endregion

// region 边权lca
template<int N, int M>
struct Lca {
    using pll = pair<ll, ll>;
    int n, mxb;
    pii e[M * 2 + 10];
    int ne[M * 2 + 10], h[N + 10], edm;
    int dep[N + 10], fa[N + 10][32];
    ll w[N + 10][32];

    Lca() {}

    void init(int _n) {
        n = _n, mxb = __lg(n);
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, int cost) {
        e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
    }

    void init_lca(int rt) {
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1;
        while (!que.empty()) {
            auto u = que.front(); que.pop();

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cost] = e[i];

                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    fa[v][0] = u, w[v][0] = cost;
                    que.push(v);

                    for (int k = 1; k <= mxb; k++) {
                        fa[v][k] = fa[fa[v][k - 1]][k - 1];
                        w[v][k] = w[v][k - 1] + w[fa[v][k - 1]][k - 1];
                    }
                }
            }
        }
    }

    pll work(int x, int y) {
        ll res = 0;
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[x][k]] >= dep[y]) {
                res += w[x][k];
                x = fa[x][k];
            }
        }
        if (x == y) return {x, res};

        for (int k = mxb; k >= 0; k--) {
            if (fa[x][k] != fa[y][k]) {
                res += w[x][k] + w[y][k];
                x = fa[x][k], y = fa[y][k];
            }
        }

        res += w[x][0] + w[y][0];
        return {fa[x][0], res};
    }
};
// endregion

// region 无边权的欧拉序lca
template<int N, int M>
struct Lca {
    int n;
    int h[N + 10], ne[2 * M + 10], e[2 * M + 10], edm;
    int id[N + 10], eula[2 * N + 10], dep[2 * N + 10], cnt;
    int st[2 * N][32];

    Lca() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void dfs(int u) {
        eula[++cnt] = u, id[u] = cnt;

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (dep[v] != -1) continue;

            dep[v] = dep[u] + 1;
            dfs(v);
            eula[++cnt] = u;
        }
    }

    void init_lca(int rt) {
        fill(dep, dep + n + 1, -1), cnt = 0;
        dep[0] = 0, dep[rt] = 1;
        dfs(rt);

        int mxb = __lg(cnt);
        for (int i = 1; i <= cnt; i++) st[i][0] = eula[i];
        for (int k = 1; k <= mxb; k++) {
            for (int i = 1; i + (1 << k) - 1 <= cnt; i++) {
                int a = st[i][k - 1];
                int b = st[i + (1 << (k - 1))][k - 1];

                st[i][k] = dep[a] < dep[b] ? a : b;
            }
        }
    }

    int work(int x, int y) {
        int L = id[x], R = id[y];
        if (L > R) swap(L, R);

        int k = __lg(R - L + 1);
        int a = st[L][k];
        int b = st[R - (1 << k) + 1][k];

        return dep[a] < dep[b] ? a : b;
    }
};
// endregion
