// region scc 无权缩点
template<int N, int M>
struct Scc {
    int n;
    int h1[N + 10], h2[N + 10], ne[2 * M + 10], e[2 * M + 10], edm;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int ins[N + 10];
    int co[N + 10], sz[N + 10], scc;

    Scc() {}

    void init(int _n) {
        n = _n, ti = 0, scc = 0;
        fill(h1, h1 + n + 1, -1), edm = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }

    void add(int h[], int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void add(int u, int v) {
        add(h1, u, v);
    }

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

    void suodian() {
        fill(h2, h2 + scc + 1, -1);

        for (int u = 1; u <= n; u++) {
            for (int i = h1[u]; ~i; i = ne[i]) {
                int v = e[i];
                if (co[u] == co[v]) continue;

                add(h2, co[u], co[v]);
            }
        }
    }
};
// endregion

// region scc 有边权缩点
template<int N, int M>
struct Scc {
    int n;
    pii e[2 * M + 10];
    int h1[N + 10], h2[N + 10], ne[2 * M + 10], edm;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int ins[N + 10];
    int co[N + 10], sz[N + 10], scc;

    Scc() {}

    void init(int _n) {
        n = _n, ti = 0, scc = 0;
        fill(h1, h1 + n + 1, -1), edm = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }

    void add(int h[], int u, int v, int cost) {
        e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
    }

    void add(int u, int v, int cost) {
        add(h1, u, v, cost);
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u), ins[u] = 1;

        for (int i = h1[u]; ~i; i = ne[i]) {
            auto [v, cost] = e[i];

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

    void suodian() {
        fill(h2, h2 + scc + 1, -1);

        for (int u = 1; u <= n; u++) {
            for (int i = h1[u]; ~i; i = ne[i]) {
                auto [v, cost] = e[i];
                if (co[u] == co[v]) continue;

                add(h2, co[u], co[v], cost);
            }
        }
    }
};
// endregion
