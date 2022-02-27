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

const int N = 1e4 + 10;

int n, m;
pii g[N * 2];
int ne[N * 2], h[N], edm;

int rt;
int dep[N], fa[N][32], w[N][32];

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void lca_init() {
    memset(dep, -1, sizeof dep), memset(fa, 0, sizeof fa), memset(w, 0x3f, sizeof w);

    queue<int> que;
    que.push(rt);
    dep[0] = 0, dep[rt] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                fa[v][0] = u, w[v][0] = cost;
                que.push(v);

                for (int k = 1; k <= 31; k++) {
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
                    w[v][k] = w[v][k - 1] + w[fa[v][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int res = 0;
    for (int k = 31; k >= 0; k--) {
        if (dep[fa[x][k]] >= dep[y]) {
            res += w[x][k];
            x = fa[x][k];
        }
    }
    if (x == y) return res;

    for (int k = 31; k >= 0; k--) {
        if (fa[x][k] != fa[y][k]) {
            res += w[x][k] + w[y][k];
            x = fa[x][k], y = fa[y][k];
        }
    }
    res += w[x][0] + w[y][0];
    return res;
}

void solve() {
    rt = 1;
    lca_init();

    while (m--) {
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> m;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n - 1; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            add(u, v, cost), add(v, u, cost);
        }

        solve();
    }

    return 0;
}