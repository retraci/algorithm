// region 无权的lca
template<int N, class G>
struct Lca {
    int n, mxb;
    int dep[N + 10], fa[__lg(N) + 1][N + 10];

    Lca() {}

    void init(int rt, const G &g) {
        n = g.n, mxb = __lg(n);
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1, fa[0][rt] = 0;
        while (!que.empty()) {
            auto u = que.front(); que.pop();

            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];

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

    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) {
                x = fa[k][x];
            }
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
template<int N, class G>
struct Lca {
    using lcat = int;
    using pit = pair<int, lcat>;

    int n, mxb;
    int dep[N + 10], fa[__lg(N) + 1][N + 10];
    lcat w[__lg(N) + 1][N + 10];

    Lca() {}

    void init(int rt, const G &g) {
        n = g.n, mxb = __lg(n);
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1, fa[0][rt] = 0, w[0][rt] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();

            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                auto [v, cost] = g.e[i];

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

    pit lca(int x, int y) {
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
template<int N, class G>
struct Lca {
    using lcat = int;

    int n;
    int id[N + 10], eula[2 * N + 10], dep[2 * N + 10], cnt;
    lcat st[__lg(2 * N) + 1][2 * N];

    Lca() {}

    void dfs(int u, const G &g) {
        eula[++cnt] = u, id[u] = cnt;

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (dep[v] != -1) continue;

            dep[v] = dep[u] + 1;
            dfs(v, g);
            eula[++cnt] = u;
        }
    }

    void init(int rt, const G &g) {
        n = g.n;
        fill(dep, dep + n + 1, -1), cnt = 0;
        dep[0] = 0, dep[rt] = 1;
        dfs(rt, g);

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

    int lca(int x, int y) {
        int L = id[x], R = id[y];
        if (L > R) swap(L, R);

        int k = __lg(R - L + 1);
        int a = st[k][L];
        int b = st[k][R - (1 << k) + 1];

        return dep[a] < dep[b] ? a : b;
    }
};
// endregion
