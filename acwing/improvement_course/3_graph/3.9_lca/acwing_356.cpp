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

const int N = 1e5 + 10;
const int M = 3e5 + 10;

int n, m;
ti3 es[M];
int pa[N];
ll mst;

int tag[M];
pii g[N * 2];
int ne[N * 2], h[N], edm;

int dep[N], fa[N][21], d1[N][21], d2[N][21];

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    pa[x] = y;
    return true;
}

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void kruskal() {
    sort(es + 1, es + m + 1, [&](auto &a, auto &b) {
        return get<0>(a) < get<0>(b);
    });
    iota(pa, pa + n + 1, 0);

    mst = 0;
    for (int i = 1; i <= m; i++) {
        auto [cost, u, v] = es[i];
        if (unite(u, v)) {
            mst += cost;
            tag[i] = 1;
        }
    }
}

void lca_init() {
    fill(dep, dep + n + 1, -1);

    dep[0] = 0, dep[1] = 1;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u, d1[v][0] = cost, d2[v][0] = -1e9;
                que.push(v);

                for (int k = 1; k <= 20; k++) {
                    int anc = fa[v][k - 1];
                    fa[v][k] = fa[anc][k - 1];
                    int tmp[4] = {d1[v][k - 1], d2[v][k - 1], d1[anc][k - 1], d2[anc][k - 1]};
                    d1[v][k] = d2[v][k] = -1e9;
                    for (int q = 0; q < 4; q++) {
                        int x = tmp[q];
                        if (x > d1[v][k]) d2[v][k] = d1[v][k], d1[v][k] = x;
                        else if (x != d1[v][k] && x > d2[v][k]) d2[v][k] = x;
                    }
                }
            }
        }
    }
}

void init() {
    kruskal();

    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [cost, u, v] = es[i];
        if (tag[i]) add(u, v, cost), add(v, u, cost);
    }

    lca_init();
}

inline int lca(int x, int y, int cost) {
    static int tmp[N * 2], cnt;
    cnt = 0;
    if (dep[x] < dep[y]) swap(x, y);
    for (int k = 20; k >= 0; k--) {
        if (dep[fa[x][k]] >= dep[y]) {
            tmp[++cnt] = d1[x][k], tmp[++cnt] = d2[x][k];
            x = fa[x][k];
        }
    }
    if (x != y) {
        for (int k = 20; k >= 0; k--) {
            if (fa[x][k] != fa[y][k]) {
                tmp[++cnt] = d1[x][k], tmp[++cnt] = d2[x][k];
                tmp[++cnt] = d1[y][k], tmp[++cnt] = d2[y][k];
                x = fa[x][k], y = fa[y][k];
            }
        }
        tmp[++cnt] = d1[x][0], tmp[++cnt] = d2[x][0];
        tmp[++cnt] = d1[y][0], tmp[++cnt] = d2[y][0];
        x = fa[x][0], y = fa[y][0];
    }

    int mx1 = -1e9, mx2 = -1e9;
    for (int i = 1; i <= cnt; i++) {
        int t = tmp[i];
        if (t > mx1) mx2 = mx1, mx1 = t;
        else if (t != mx1 && t > mx2) mx2 = t;
    }
    return mx1 == cost ? mx2 : mx1;
}

void solve() {
    init();

    ll ans = 1e18;
    for (int i = 1; i <= m; i++) {
        auto [cost, u, v] = es[i];
        if (tag[i]) continue;

        int mx = lca(u, v, cost);
        ans = min(ans, mst - mx + cost);
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
            es[i] = {cost, u, v};
        }
        solve();
    }

    return 0;
}