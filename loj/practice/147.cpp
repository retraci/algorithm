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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e6 + 10;

int n, q, rt;
int a[N];
Graph<N, N> g;
Fenwick<N> fw1, fw2;
int in[N], out[N], id[N], ti;
int dep[N], fa[N];
Lca<N, Graph<N, N>> lca;

void pdfs(int u, int fno) {
    id[++ti] = u, in[u] = ti;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        fa[v] = u;
        dep[v] = dep[u] + 1;
        pdfs(v, u);
    }

    out[u] = ti;
}

ll get(int u) {
    return fw1.qr(in[u]) + 1LL * (dep[u] + 1) * fw2.qr(in[u]);
}

void solve() {
    dep[rt] = 1;
    pdfs(rt, -1);

    fw1.init(n + 1), fw2.init(n + 1);
    lca.init(rt, g);
    for (int i = 1; i <= n; i++) {
        int L = in[i], R = out[i];
        fw1.upd(L, a[i]);
        fw1.upd(R + 1, -a[i]);
    }

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int u, x;
            cin >> u >> x;

            int L = in[u], R = out[u];
            fw1.upd(L, x);
            fw1.upd(R + 1, -x);
        }
        if (op == 2) {
            int u, x;
            cin >> u >> x;

            int L = in[u], R = out[u];
            fw1.upd(L, 1LL * dep[u] * -x);
            fw1.upd(R + 1, 1LL * dep[u] * x);
            fw2.upd(L, x);
            fw2.upd(R + 1, -x);
        }
        if (op == 3) {
            int u, v;
            cin >> u >> v;

            int ca = lca.lca(u, v), caa = fa[ca];
            ll t = get(u) + get(v) - get(ca) - get(caa);
            cout << t << "\n";
        }
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
        cin >> n >> q >> rt;
        for (int i = 1; i <= n; i++) cin >> a[i];
        g.init(n, -1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v);
            g.add(v, u);
        }
        solve();
    }

    return 0;
}