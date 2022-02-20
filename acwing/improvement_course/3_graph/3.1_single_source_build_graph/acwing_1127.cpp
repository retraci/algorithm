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

const int N = 810;
const int M = 1450 + 10;

int c, n, m;
int va[N];
pii g[M * 2];
int ne[M * 2], h[N], edm;

void add(int u, int v, int cost) {
    g[edm] = {v, cost};
    ne[edm] = h[u], h[u] = edm++;
}

int dij(int s) {
    int dist[n + 1], vis[n + 1];
    fill(&dist[1], &dist[n] + 1, 1e9), memset(vis, 0, sizeof vis);

    priority_queue<pii> que;
    que.push({0, s});
    dist[s] = 0;
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cost] = g[i];
            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push({-dist[v], v});
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= c; i++) {
        if (dist[va[i]] == 1e9) return 1e9;
        res += dist[va[i]];
    }
    return res;
}

void solve() {
    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dij(i));
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
        cin >> c >> n >> m;
            for (int i = 1; i <= c; i++) cin >> va[i];
        memset(h, -1, sizeof h);
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            add(u, v, cost), add(v, u, cost);
        }
        solve();
    }

    return 0;
}