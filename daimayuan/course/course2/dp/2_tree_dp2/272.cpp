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

// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = ll;

    int n;
    fwt tr[SZ + 10];

    Fenwick() {}

    void init(int _n) {
        n = _n;
        fill(tr, tr + n + 1, 0);
    }

    void upd(int id, fwt x) {
        assert(id > 0);
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    int kth(fwt x) {
        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && tr[pos + (1 << i)] < x) {
                pos += 1 << i;
                x -= tr[pos];
            }
        }

        return pos + 1;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 2010;

int n, m;
Graph<N, N> g;
ai3 a[N];
Lca<N, Graph<N, N>> lca;
vector<int> paid[N];
int in[N], out[N], id[N], ti;
int fa[N];
Fenwick<N> fw;
ll f[N], sf[N];

void pdfs(int u, int fno) {
    id[++ti] = u, in[u] = ti;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        fa[v] = u;
        pdfs(v, u);
    }

    out[u] = ti;
}

void dfs(int u, int fno) {
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);

        sf[u] += f[v];
    }

    f[u] = sf[u];
    for (int pid : paid[u]) {
        auto [tu, tv, cost] = a[pid];

        ll t = sf[u] + fw.qr(in[tu]) + fw.qr(in[tv]) - 2 * fw.qr(in[u]);

        f[u] = max(f[u], t + cost);
    }

    int L = in[u], R = out[u];
    fw.upd(L, sf[u] - f[u]), fw.upd(R + 1, -(sf[u] - f[u]));
}

void solve() {
    lca.init(1, g);

    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = a[i];
        int ca = lca.lca(u, v);
        paid[ca].push_back(i);
    }

    pdfs(1, -1);
    fw.init(n + 1);
    dfs(1, -1);

    cout << f[1] << "\n";
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
        g.init(n, -1);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            g.add(p, i);
        }
        for (int i = 1; i <= m; i++) cin >> a[i][0] >> a[i][1] >> a[i][2];
        solve();
    }

    return 0;
}