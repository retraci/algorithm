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
const int M = 500010;

int n, m;
int va[N];
ti3 vb[M];
ti3 g[M * 2 * 3];
int ne[M * 2 * 3], h[3][N], edm;

int dist[3][N];
int vis[3][N];

void add(int lu, int u, int lv, int v, int cost) {
    g[edm] = {cost, lv, v};
    ne[edm] = h[lu][u], h[lu][u] = edm++;
}

void init() {
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= m; j++) {
            auto [u, v, t] = vb[j];
            add(i, u, i, v, 0);
            if (t == 2) add(i, v, i, u, 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        add(0, i, 1, i, va[i] + 100);
        add(1, i, 2, i, -va[i] + 100);
    }
}

struct Node {
    int d, lu, u;

    bool operator< (const Node &rhs) const {
        return d > rhs.d;
    }
};

void dij() {
    fill(&dist[0][0], &dist[2][n] + 1, 1e9);

    priority_queue<Node> pq;
    dist[0][1] = 0;
    pq.push({0, 0, 1});
    while (!pq.empty()) {
        auto [d, lu, u] = pq.top(); pq.pop();
        if (vis[lu][u]) continue;
        vis[lu][u] = 1;

        for (int i = h[lu][u]; ~i; i = ne[i]) {
            auto [cost, lv, v] = g[i];

            if (dist[lv][v] > dist[lu][u] + cost) {
                dist[lv][v] = dist[lu][u] + cost;
                pq.push({dist[lv][v], lv, v});
            }
        }
    }
}

void solve() {
    init();

    dij();

    int ans = max(0, -dist[2][n] + 200);
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
        memset(h, -1, sizeof h);

        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= m; i++) {
            int u, v, t;
            cin >> u >> v >> t;
            vb[i] = {u, v, t};
        }

        solve();
    }

    return 0;
}