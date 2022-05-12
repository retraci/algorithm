// region e-dcc
template<int N, int M>
struct EDcc {
    int n;
    int e[4 * M + 10], ne[4 * M + 10], h1[N + 10], h2[N + 10], edm;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int co[N + 10], sz[N + 10], dcc;
    int br[2 * M + 10];

    EDcc() {}

    void init(int _n, int _m) {
        n = _n, ti = 0, dcc = 0;
        fill(h1, h1 + n + 1, -1), edm = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
        fill(br, br + 2 * _m + 1, 0);
    }

    void add(int h[], int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void add(int u, int v) {
        add(h1, u, v);
    }

    void tarjan(int u, int pe) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u);

        for (int i = h1[u]; ~i; i = ne[i]) {
            int v = e[i];
            if ((i ^ 1) == pe) continue;

            if (!dfn[v]) {
                tarjan(v, i);
                low[u] = min(low[u], low[v]);

                if (low[v] > dfn[u]) br[i] = br[i ^ 1] = 1;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            dcc++;
            int t;
            do {
                t = stk.back(); stk.pop_back();
                co[t] = dcc;
                sz[dcc]++;
            } while (t != u);
        }
    }

    void suodian() {
        fill(h2, h2 + dcc + 1, -1);

        for (int u = 1; u <= n; u++) {
            for (int i = h1[u]; ~i; i = ne[i]) {
                int v = e[i];
                if (co[u] == co[v]) continue;

                add(h2, co[u], co[v]), add(h2, co[v], co[u]);
            }
        }
    }
};
// endregion

// region v-dcc
template<int N, int M>
struct VDcc {
    int n;
    int e[4 * M + 10], ne[4 * M + 10], h1[N + 10], h2[N + 10], edm;
    int dfn[N + 10], low[N + 10], ti, rt;
    vector<int> stk;
    vector<int> cc[N + 10];
    int cut[N + 10], dcc;

    void init(int _n) {
        n = _n, ti = 0, dcc = 0;
        fill(h1, h1 + n + 1, -1), edm = 0;
        fill(dfn, dfn + n + 1, 0);
        for (int i = 1; i <= n; i++) cc[i] = {};
        fill(cut, cut + n + 1, 0);
    }

    void add(int h[], int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void add(int u, int v) {
        add(h1, u, v);
    }

    void tarjan(int u, int pe) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u);

        if (u == rt && h1[u] == -1) {
            dcc++;
            cc[dcc].push_back(u);
            return;
        }

        int cnt = 0;
        for (int i = h1[u]; ~i; i = ne[i]) {
            int v = e[i];
            if ((i ^ 1) == pe) continue;

            if (!dfn[v]) {
                tarjan(v, i);
                low[u] = min(low[u], low[v]);

                if (low[v] >= dfn[u]) {
                    if (++cnt >= 2 || u != rt) cut[u] = 1;

                    dcc++;
                    int t;
                    do {
                        t = stk.back(); stk.pop_back();
                        cc[dcc].push_back(t);
                    } while (t != v);
                    cc[dcc].push_back(u);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
};
// endregion
