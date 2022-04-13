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

const int N = 2e5 + 10;

int n, m;
int a[N];
pii es[N];

int h[N], ne[2 * N], edm;
pii e[2 * N];

ll dist[N], vis[N];

void add(int u, int v, int cost) {
    e[edm] = {cost, v}; ne[edm] = h[u], h[u] = edm++;
}

void init() {
    fill(h, h + n + 1, -1), edm = 0;

    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        int c1 = a[u] > a[v] ? a[u] - a[v] : -2 * (a[v] - a[u]);
        int c2 = a[v] > a[u] ? a[v] - a[u] : -2 * (a[u] - a[v]);
        add(u, v, -c1 + a[u] - a[v]);
        add(v, u, -c2 + a[v] - a[u]);
    }
}

void dij() {
    fill(dist, dist + n + 1, 1e18);
    fill(vis, vis + n + 1, 0);

    priority_queue<pll> que;
    que.push({0, 1});
    dist[1] = 0;
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = e[i];

            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                que.push({-dist[v], v});
            }
        }
    }
}

void solve() {
    init();

    dij();
    for (int i = 1; i <= n; i++) {
        dist[i] = -(dist[i] - (a[1] - a[i]));
    }
    ll ans = *max_element(dist + 1, dist + n + 1);
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            es[i] = {u, v};
        }
        solve();
    }

    return 0;
}