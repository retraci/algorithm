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
const int M = 2e5 + 10;
const int MOD = 100003;

int n, m;
int g[M * 2];
int ne[M * 2], h[N], edm;

int dist[N], cnt[N];

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void bfs() {
    memset(dist, -1, sizeof dist), memset(cnt, 0, sizeof cnt);

    queue<int> que;
    que.push(1);
    dist[1] = 0, cnt[1] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = g[i];

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];
                que.push(v);
            } else if (dist[v] == dist[u] + 1) {
                cnt[v] += cnt[u];
                cnt[v] %= MOD;
            }
        }
    }
}

void solve() {
    bfs();

    for (int i = 1; i <= n; i++) cout << cnt[i] << "\n";
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
        memset(h, -1, sizeof h), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}