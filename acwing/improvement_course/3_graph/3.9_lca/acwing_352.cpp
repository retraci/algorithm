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

const int N = 100010;
const int M = 200010;

int n, m;
pii es[M];
int g[N * 2], ne[N * 2], h[N], edm;
int d[N];
int ans;

int dep[N], fa[N][17];

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void lca_init() {
    fill(dep, dep + n + 1, -1);

    dep[0] = 0, dep[1] = 1;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = g[i];

            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u;
                que.push(v);

                for (int k = 1; k <= 16; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int k = 16; k >= 0; k--) {
        if (dep[fa[x][k]] >= dep[y]) x = fa[x][k];
    }
    if (x == y) return x;

    for (int k = 16; k >= 0; k--) {
        if (fa[x][k] != fa[y][k]) x = fa[x][k], y = fa[y][k];
    }
    return fa[x][0];
}

int dfs(int u, int fno) {
    int res = d[u];

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;

        int ret = dfs(v, u);
        if (ret == 0) ans += m;
        else if (ret == 1) ans += 1;
        res += ret;
    }

    return res;
}

void solve() {
    lca_init();

    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        int p = lca(u, v);
        d[u]++, d[v]++, d[p] -= 2;
    }

    ans = 0;
    dfs(1, 0);
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        for (int i = 1; i <= m; i++) cin >> es[i].fi >> es[i].se;

        solve();
    }

    return 0;
}