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

const int N = 110;
const int M = N * N;

int n, m;
int vp[N], vl[N];
pii g[M * 2];
int ne[M * 2], h[N], edm;

void add(int u, int v, int cost) {
    g[edm] = {v, cost};
    ne[edm] = h[u], h[u] = edm++;
}

int dij(int L, int R) {
    int dist[n + 1], vis[n + 1];
    memset(dist, 0x3f, sizeof dist), memset(vis, 0, sizeof vis);

    priority_queue<pii> que;
    que.push({0, 0});
    dist[0] = 0;
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cost] = g[i];
            if (vl[v] >= L && vl[v] <= R && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push({-dist[v], v});
            }
        }
    }

    return dist[1];
}

void solve() {
    for (int i = 1; i <= n; i++) add(0, i, vp[i]);

    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dij(i, i + m));
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
        cin >> m >> n;
        memset(h, -1, sizeof h);

        for (int i = 1; i <= n; i++) {
            int cnt;
            cin >> vp[i] >> vl[i] >> cnt;
            for (int j = 1; j <= cnt; j++) {
                int u, cost;
                cin >> u >> cost;
                add(u, i, cost);
            }
        }
        solve();
    }

    return 0;
}