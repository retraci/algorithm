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

const int N = 510;
const int M = 1e4 + 10;

int n, m;
ti3 es[M];

pii g[N * 2];
int ne[N * 2], h[N], edm;
pii mx[N][N];

int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void dfs(int rt, int u, int fno, int mx1, int mx2) {
    mx[rt][u] = {mx1, mx2};

    for (int i = h[u]; ~i; i = ne[i]) {
        auto [cost, v] = g[i];
        if (v == fno) continue;

        int nmx1 = mx1, nmx2 = mx2;
        if (cost > nmx1) {
            nmx2 = nmx1;
            nmx1 = cost;
        } else if (cost != nmx1 && cost > nmx2) {
            nmx2 = cost;
        }
        dfs(rt, v, u, nmx1, nmx2);
    }
}

void solve() {
    sort(es + 1, es + m + 1);
    iota(fa, fa + n + 1, 0);
    vector<int> vis(m + 1, 0);

    ll mst = 0;
    for (int i = 1; i <= m; i++) {
        auto [cost, u, v] = es[i];
        if (unite(u, v)) {
            vis[i] = 1;
            mst += cost;
        }
    }

    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        if (!vis[i]) continue;
        auto [cost, u, v] = es[i];
        add(u, v, cost), add(v, u, cost);
    }

    for (int i = 1; i <= n; i++) {
        dfs(i, i, 0, 0, 0);
    }

    ll ans = 1e18;
    for (int i = 1; i <= m; i++) {
        if (vis[i]) continue;
        auto [cost, u, v] = es[i];
        auto [mx1, mx2] = mx[u][v];

        if (mx1 != 0) {
            ll tmp = mst + cost - mx1;
            if (tmp != mst) ans = min(ans, tmp);
        }
        if (mx2 != 0) {
            ll tmp = mst + cost - mx2;
            if (tmp != mst) ans = min(ans, tmp);
        }
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