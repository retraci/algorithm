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

const int N = 1010;
const int M = 2e4 + 10;

int n, m;
int s, t, k;
pii g[M];
int h[N], rh[N], ne[M], edm;

int dist[N];
int vis[N];

void add(int *hh, int u, int v, int cost) {
    g[edm] = {v, cost};
    ne[edm] = hh[u], hh[u] = edm++;
}

void dij() {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<pii> que;
    dist[t] = 0;
    que.push({0, t});
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = rh[u]; ~i; i = ne[i]) {
            auto [v, cost] = g[i];
            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push({-dist[v], v});
            }
        }
    }
}

void solve() {
    dij();

    if (s == t) k++;
    memset(vis, 0, sizeof vis);
    priority_queue<ti3> que;
    que.push({-dist[s], 0, s});
    while (!que.empty()) {
        auto [f, d, u] = que.top(); que.pop(); d = -d;
        vis[u]++;
        if (vis[t] == k) {
            cout << d << "\n";
            return;
        }

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cost] = g[i];
            int nd = d + cost;
            int nf = nd + dist[v];
            if (vis[v] < k) que.push({-nf, -nd, v});
        }
    }

    cout << -1 << "\n";
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
        memset(h, -1, sizeof h), memset(rh, -1, sizeof rh);
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            add(h, u, v, cost), add(rh, v, u, cost);
        }
        cin >> s >> t >> k;
        solve();
    }

    return 0;
}