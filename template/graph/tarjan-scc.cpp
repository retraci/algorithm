// region 无边权 scc
template<int N, class G>
struct Tarjan {
    int n;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int ins[N + 10];
    int co[N + 10], sz[N + 10], scc;

    Tarjan() {}

    void init(int _n) {
        n = _n, ti = 0, scc = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }

    void tarjan(int u, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u), ins[u] = 1;

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];

            if (!dfn[v]) {
                tarjan(v, g);
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

    // 有重边
    G suodian(const G &g) {
        G res;
        res.init(scc, -1);

        for (int u = 1; u <= n; u++) {
            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];
                if (co[u] == co[v]) continue;

                res.add(co[u], co[v]);
            }
        }

        return res;
    }
};
// endregion

// region 有边权 scc
template<int N, class G>
struct Tarjan {
    int n;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int ins[N + 10];
    int co[N + 10], sz[N + 10], scc;

    Tarjan() {}

    void init(int _n) {
        n = _n, ti = 0, scc = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }

    void tarjan(int u, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u), ins[u] = 1;

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            auto [v, cost] = g.e[i];

            if (!dfn[v]) {
                tarjan(v, g);
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

    // 有重边
    G suodian(const G &g) {
        G res;
        res.init(scc, -1);
        for (int u = 1; u <= n; u++) {
            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                auto [v, cost] = g.e[i];
                if (co[u] == co[v]) continue;

                res.add(co[u], co[v], cost);
            }
        }

        return res;
    }
};
// endregion
