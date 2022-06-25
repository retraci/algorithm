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

using ull = unsigned long long;
ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

pair<int, int> myRanq(ull &k1, ull &k2, int MAXN) {
    int x = myRand(k1, k2) % MAXN + 1, y = myRand(k1, k2) % MAXN + 1;
    if (x > y)return make_pair(y, x);
    else return make_pair(x, y);
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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 5e5 + 10;

using G = Graph<2 * N, M>;

int n, m;
ai3 es[M];
int w[2 * N], tt;
G g;
Dsu<2 * N> dsu;
Lca<2 * N, G> lca;

void init() {
    sort(es + 1, es + m + 1, [](auto &a, auto &b) {
        return a[2] < b[2];
    });

    dsu.init(2 * n);
    g.init(2 * n + 1, -1);
    tt = n;
    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = es[i];
        int tu = dsu.find(u), tv = dsu.find(v);
        if (tu == tv) continue;

        tt++;
        dsu.unite(tu, tt), dsu.unite(tv, tt);
        g.add(tt, tu), g.add(tt, tv);
        w[tt] = cost;
    }

    lca.init(tt, g);
}

void solve() {
    init();

    int ans = 0;
    ull Q, a1, a2;
    cin >> Q >> a1 >> a2;
    while (Q--) {
        auto[x, y] = myRanq(a1, a2, n);

        int tmp = w[lca.lca(x, y)];
        ans ^= tmp;
    }
    cout << ans << "\n";
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
    int T = 1;
//    cin >> T;
    while (T--) {
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