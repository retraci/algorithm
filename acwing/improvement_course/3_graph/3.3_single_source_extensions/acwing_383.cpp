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
const int M = 20010;

int n, m, s, t;
pii g[M * 2];
int ne[M * 2], h[N], edm;

int dist[N][2], cnt[N][2];
int vis[N][2];

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void dij() {
    fill(&dist[0][0], &dist[n][1] + 1, 1e9);
    fill(&cnt[0][0], &cnt[n][1] + 1, 0);
    fill(&vis[0][0], &vis[n][1] + 1, 0);

    priority_queue<ti3> pq;
    pq.push({0, s, 0});
    dist[s][0] = 0, cnt[s][0] = 1;
    while (!pq.empty()) {
        auto [d, u, ty] = pq.top(); pq.pop(); d = -d;
        if (vis[u][ty]) continue;
        vis[u][ty] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v][0] > d + cost) {
                dist[v][1] = dist[v][0], cnt[v][1] = cnt[v][0];
                pq.push({-dist[v][1], v, 1});
                dist[v][0] = d + cost, cnt[v][0] = cnt[u][ty];
                pq.push({-dist[v][0], v, 0});
            } else if (dist[v][0] == d + cost) {
                cnt[v][0] += cnt[u][ty];
            } else if (dist[v][0] < d + cost && dist[v][1] > d + cost) {
                dist[v][1] = d + cost, cnt[v][1] = cnt[u][ty];
                pq.push({-dist[v][1], v, 1});
            } else if (dist[v][1] == d + cost) {
                cnt[v][1] += cnt[u][ty];
            }
        }
    }
}

void solve() {
    dij();

    int ans = cnt[t][0];
    if (dist[t][0] + 1 == dist[t][1]) ans += cnt[t][1];
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
    cin >> T;
    while (T--) {
        cin >> n >> m;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            add(u, v, cost);
        }
        cin >> s >> t;
        solve();
    }

    return 0;
}