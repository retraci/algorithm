#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

// region e-dcc
template<int N, int M, class G>
struct EDcc {
    int n, m;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int co[N + 10], sz[N + 10], dcc;
    int br[2 * M + 10];

    EDcc() {}

    void init(int _n, int _m) {
        n = _n, m = _m, ti = 0, dcc = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
        fill(br, br + 2 * m + 1, 0);
    }

    // 重边合法 => pe, 重边不合法 => fno
    void tarjan(int u, int fno, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u);

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (v == fno) continue;

            if (!dfn[v]) {
                tarjan(v, u, g);
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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;
const int M = 200010;

using G = Graph<N, M>;

int n, m;
G g;
EDcc<N, M, G> edcc;
Lca<N, G> lca;
Dsu<N> dsu;

void solve() {
    edcc.init(n, m);
    edcc.tarjan(1, -1, g);
    auto ng = edcc.suodian(g);
    int dcc = edcc.dcc;
    lca.init(edcc.co[1], ng);

    static char buf[111];
    static int CA = 0;
    sprintf(buf, "Case %d:", ++CA);
    cout << string(buf) << "\n";

    dsu.init(dcc);
    int cur = dcc - 1;
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;

        x = dsu.find(edcc.co[x]), y = dsu.find(edcc.co[y]);
        int tar = lca.lca(x, y);
        while (lca.dep[x] > lca.dep[tar]) {
            dsu.fa[x] = lca.fa[0][x];
            cur--;
            x = dsu.find(x);
        }
        while (lca.dep[y] > lca.dep[tar]) {
            dsu.fa[y] = lca.fa[0][y];
            cur--;
            y = dsu.find(y);
        }
        cout << cur << "\n";
    }

    cout << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (cin >> n >> m, n) {
        g.init(n, m);
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v), g.add(v, u);
        }
        solve();
    }

    return 0;
}