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

const int N = 200010;
const int M = 400010;

int n, m;
ti4 es[M];

int g[2 * N], h[2 * N], ne[2 * M], edm;
int w[2 * N], pa[2 * N], tt;

pii g1[2 * M];
int dist[N];

int mi[2 * N];

// region 无边权的lca
int dep[2 * N], fa[2 * N][23];

void lca_init(int rt) {
    fill(dep, dep + tt + 1, -1);

    queue<int> que;
    que.push(rt);
    dep[0] = 0, dep[rt] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = g[i];

            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u;
                que.push(v);

                for (int k = 1; k <= 22; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                }
            }
        }
    }
}
// endregion

void add(int u, int v) {
    g[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void add(int u, int v, int cost) {
    g1[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

bool unite(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return false;
    pa[tx] = ty;
    return true;
}

void dij() {
    fill(dist, dist + n + 1, 2e9);
    vector<int> vis(n + 1, 0);

    priority_queue<pii> que;
    dist[1] = 0;
    que.push({0, 1});
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g1[i];

            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push({-dist[v], v});
            }
        }
    }
}

void dfs(int u) {
    mi[u] = u <= n ? dist[u] : 2e9;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        dfs(v);
        mi[u] = min(mi[u], mi[v]);
    }
}

void init() {
    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [u, v, l, a] = es[i];
        add(u, v, l), add(v, u, l);
    }
    dij();

    sort(es + 1, es + m + 1, [](auto &a, auto &b) {
        return get<3>(a) > get<3>(b);
    });

    tt = n;
    fill(h, h + 2 * n + 1, -1), edm = 0;
    iota(pa, pa + 2 * n + 1, 0);
    for (int i = 1; i <= m; i++) {
        auto [u, v, l, a] = es[i];
        int tu = find(u), tv = find(v);
        if (tu == tv) continue;

        tt++;
        unite(tu, tt), unite(tv, tt);
        add(tt, tu), add(tt, tv);
        w[tt] = a;
    }
    dfs(tt);

    lca_init(tt);
}

void solve() {
    init();

    ll lst = 0;
    ll q, k, s;
    cin >> q >> k >> s;
    while (q--) {
        ll v0, p0;
        cin >> v0 >> p0;
        ll v = (v0 + k * lst - 1) % n + 1;
        ll p = (p0 + k * lst) % (s + 1);

        for (int i = 22; i >= 0; i--) {
            if (!fa[v][i]) continue;
            if (w[fa[v][i]] > p) v = fa[v][i];
        }
        lst = mi[v];
        cout << lst << "\n";
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
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int u, v, l, a;
            cin >> u >> v >> l >> a;
            es[i] = {u, v, l, a};
        }
        solve();
    }

    return 0;
}