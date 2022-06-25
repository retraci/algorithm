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
template <int SZ>
struct Dsu {
    int pa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(pa, pa + _n + 1, 0);
    }

    int find(int x) {
        return x == pa[x] ? x : pa[x] = find(pa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        pa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
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
                w[k][v] = max(w[k - 1][v], w[k - 1][fa[k - 1][v]]);
            }
        }
    }

    pit lca(int x, int y) {
        lcat res = 0;
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) {
                res = max(res, w[k][x]);
                x = fa[k][x];
            }
        }
        if (x == y) return {x, res};

        for (int k = mxb; k >= 0; k--) {
            if (fa[k][x] != fa[k][y]) {
                res = max({res, w[k][x], w[k][y]});
                x = fa[k][x], y = fa[k][y];
            }
        }

        res = max({res, w[0][x], w[0][y]});
        return {fa[0][x], res};
    }
};
// endregion

// region 带权图
template<int N, int M>
struct Graph {
    using gt = int;
    using pit = pair<int, gt>;

    int n, m;
    pit e[M * 2 + 10];
    int h[N + 10], ne[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, gt cost) {
        e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 1e6 + 10;

using G = Graph<N, M>;

int n, m;
ai3 es[M];
Dsu<N> dsu;
G g;
Lca<N, G> lca;

void init() {
    dsu.init(n);

    sort(es + 1, es + m + 1, [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });

    g.init(n, m);
    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = es[i];

        if (dsu.unite(u, v)) g.add(u, v, cost), g.add(v, u, cost);
    }

    lca.init(1, g);
}

void solve() {
    init();

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u, v).se << "\n";
    }
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
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            es[i] = {u, v, cost};
        }

        solve();
    }

    return 0;
}