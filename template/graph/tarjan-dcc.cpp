// region 无边权 e-dcc
template<int N, int M, class G>
struct Tarjan {
    int n, m;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int co[N + 10], sz[N + 10], dcc;
    int br[2 * M + 10];

    Tarjan() {}

    void init(int _n, int _m) {
        n = _n, m = _m, ti = 0, dcc = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
        fill(br, br + 2 * m + 1, 0);
    }

    // 重边合法 => pe, 重边不合法 => fno
    void tarjan(int u, int pe, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u);

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if ((i ^ 1) == pe) continue;

            if (!dfn[v]) {
                tarjan(v, i, g);
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

    // 有重边
    G suodian(const G &g) {
        G res;
        res.init(dcc, 0);

        for (int u = 1; u <= n; u++) {
            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];
                if (co[u] == co[v]) continue;

                res.add(co[u], co[v]), res.add(co[v], co[u]);
            }
        }

        return res;
    }
};
// endregion

// region 无边权 v-dcc
template<int N, class G>
struct Tarjan {
    int n;
    int dfn[N + 10], low[N + 10], ti, rt;
    vector<int> stk;
    vector<int> cc[N + 10];
    int cut[N + 10], dcc;

    Tarjan() {}

    void init(int _n) {
        n = _n, ti = 0, dcc = 0;
        fill(dfn, dfn + n + 1, 0);
        for (int i = 1; i <= n; i++) cc[i].clear();
        fill(cut, cut + n + 1, 0);
    }

    // 由于判割点, tarjan前给rt赋值: tarjan(g.rt = u, -1);
    // 重边合法 => pe, 重边不合法 => fno
    void tarjan(int u, int pe, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u);

        if (u == rt && g.h[u] == -1) {
            dcc++;
            cc[dcc].push_back(u);
            return;
        }

        int cnt = 0;
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if ((i ^ 1) == pe) continue;

            if (!dfn[v]) {
                tarjan(v, i, g);
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
