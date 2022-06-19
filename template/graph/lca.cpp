// region 无权的lca
template<int N, int M>
struct Lca {
    int n, mxb;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;
    int dep[N + 10], fa[32][N + 10];

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
                    fa[0][v] = u;
                    que.push(v);
                }
            }
        }

        for (int k = 1; k <= mxb; k++) {
            for (int v = 1; v <= n; v++) {
                fa[k][v] = fa[k - 1][fa[k - 1][v]];
            }
        }
    }

    int work(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) x = fa[k][x];
        }
        if (x == y) return x;

        for (int k = mxb; k >= 0; k--) {
            if (fa[k][x] != fa[k][y]) {
                x = fa[k][x], y = fa[k][y];
            }
        }
        return fa[0][x];
    }
};
// endregion

// region 边权lca
template<int N, int M>
struct Lca {
    using lcat = int;
    using pit = pair<int, lcat>;
    
    int n, mxb;
    pit e[M * 2 + 10];
    int ne[M * 2 + 10], h[N + 10], edm;
    int dep[N + 10], fa[32][N + 10];
    lcat w[32][N + 10];

    Lca() {}

    void init(int _n) {
        n = _n, mxb = __lg(n);
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, lcat cost) {
        e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
    }

    void init_lca(int rt) {
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1;
        while (!que.empty()) {
            int u = que.front(); que.pop();

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cost] = e[i];

                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    fa[0][v] = u, w[0][v] = cost;
                    que.push(v);
                }
            }
        }

        for (int k = 1; k <= mxb; k++) {
            for (int v = 1; v <= n; v++) {
                fa[k][v] = fa[k - 1][fa[k - 1][v]];
                w[k][v] = w[k - 1][v] + w[k - 1][fa[k - 1][v]];
            }
        }
    }

    pit work(int x, int y) {
        lcat res = 0;
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) {
                res += w[k][x];
                x = fa[k][x];
            }
        }
        if (x == y) return {x, res};

        for (int k = mxb; k >= 0; k--) {
            if (fa[k][x] != fa[k][y]) {
                res += w[k][x] + w[k][y];
                x = fa[k][x], y = fa[k][y];
            }
        }

        res += w[0][x] + w[0][y];
        return {fa[0][x], res};
    }
};
// endregion

// region 无边权的欧拉序lca
template<int N, int M>
struct Lca {
    int n;
    int h[N + 10], ne[2 * M + 10], e[2 * M + 10], edm;
    int id[N + 10], eula[2 * N + 10], dep[2 * N + 10], cnt;
    int st[32][2 * N];

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
        for (int i = 1; i <= cnt; i++) st[0][i] = eula[i];
        for (int k = 1; k <= mxb; k++) {
            for (int i = 1; i + (1 << k) - 1 <= cnt; i++) {
                int a = st[k - 1][i];
                int b = st[k - 1][i + (1 << (k - 1))];

                st[k][i] = dep[a] < dep[b] ? a : b;
            }
        }
    }

    int work(int x, int y) {
        int L = id[x], R = id[y];
        if (L > R) swap(L, R);

        int k = __lg(R - L + 1);
        int a = st[k][L];
        int b = st[k][R - (1 << k) + 1];

        return dep[a] < dep[b] ? a : b;
    }
};
// endregion
