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

int n, m, v1, v2;
pii g[N * 2];
int ne[N * 2], h[N], edm;
int k, a[22], p[22];

int d[22][22];

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void dij(int S) {
    vector<int> dist(n + 1, 1e9), vis(n + 1, 0);
    priority_queue<pii> que;
    dist[a[S]] = 0;
    que.push({0, a[S]});
    while (!que.empty()) {
        auto [w, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push({-dist[v], v});
            }
        }
    }

    for (int i = 0; i <= k + 1; i++) {
        int v = a[i];
        d[S][i] = d[i][S] = dist[v];
    }
}

void init() {
    fill(&d[0][0], &d[k + 1][k + 1] + 1, 1e9);
    a[k] = 1, a[k + 1] = n;
    for (int i = 0; i <= k + 1; i++) dij(i);
}

void solve() {
    init();

    if (d[k][k + 1] == 1e9) {
        cout << -1 << "\n";
        return;
    }

    int lim = 1 << k;
    double f[lim][k];
    for (int mask = lim - 1; mask >= 0; mask--) {
        for (int i = 0; i < k; i++) {
            if (mask >> i & 1) {
                double p1 = p[i] / 100.0;
                double t1 = 1.0 * d[i][k + 1] / v1;
                double t2 = 1.0 * d[i][k + 1] / v2;

                for (int j = 0; j < k; j++) {
                    if (mask >> j & 1) continue;
                    int ns = mask | (1 << j);
                    t1 = min(t1, 1.0 * d[i][j] / v1 + f[ns][j]);
                }

                f[mask][i] = p1 * t1 + (1 - p1) * t2;
            }
        }
    }

    double ans = 1.0 * d[k][k + 1] / v1;
    for (int i = 0; i < k; i++) {
        ans = min(ans, 1.0 * d[k][i] / v1 + f[1 << i][i]);
    }
    cout << fixed << setprecision(6);
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
        cin >> v1 >> v2;
        cin >> n >> m;
        fill(h, h + n + 1, -1), edm = 0;

        while (m--) {
            int u, v, cost;
            cin >> u >> v >> cost;
            add(u, v, cost), add(v, u, cost);
        }

        cin >> k;
        for (int i = 0; i < k; i++) cin >> a[i] >> p[i];

        solve();
    }

    return 0;
}