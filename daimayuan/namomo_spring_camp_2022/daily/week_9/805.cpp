#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1e5 + 10, M = 1e6 + 10;

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

// region 有边权的lca
int n, m;
pii e[M * 2];
int ne[M * 2], h[N], edm;
int dep[N], fa[N][32];
ll w[N][32];

void add(int u, int v, int cost) {
    e[edm] = {cost, v}, ne[edm] = h[u], h[u] = edm++;
}

void lca_init(int rt) {
    fill(dep, dep + n + 1, -1);

    queue<int> que;
    que.push(rt);
    dep[0] = 0, dep[rt] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = e[i];

            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u, w[v][0] = cost;
                que.push(v);

                for (int k = 1; k <= 31; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                    w[v][k] = max(w[v][k - 1], w[fa[v][k - 1]][k - 1]);
                }
            }
        }
    }
}

ll lca(int x, int y) {
    ll res = 0;
    if (dep[x] < dep[y]) swap(x, y);
    for (int k = 31; k >= 0; k--) {
        if (dep[fa[x][k]] >= dep[y]) {
            res = max(res, w[x][k]);
            x = fa[x][k];
        }
    }
    if (x == y) return res;

    for (int k = 31; k >= 0; k--) {
        if (fa[x][k] != fa[y][k]) {
            res = max({res, w[x][k], w[y][k]});
            x = fa[x][k], y = fa[y][k];
        }
    }
    res = max({res, w[x][0], w[y][0]});
    return res;
}
// endregion

ti3 es[M];
Dsu<N> dsu;

void init() {
    dsu.init(n);

    sort(es + 1, es + m + 1, [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });
    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = es[i];

        if (dsu.unite(u, v)) add(u, v, cost), add(v, u, cost);
    }

    lca_init(1);
}

void solve() {
    init();

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
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