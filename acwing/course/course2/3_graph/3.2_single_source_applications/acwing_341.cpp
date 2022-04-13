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
int g[M * 4];
int ne[M * 4], h[N], rh[N], edm;

int dmi[N], dmx[N];

void add(int *hh, int u, int v) {
    g[edm] = v;
    ne[edm] = hh[u], hh[u] = edm++;
}

void spfa(int *hh, int *dist, int type) {
    vector<int> inq(n + 1, 0);
    deque<int> que;
    if (type) {
        fill(&dist[1], &dist[n] + 1, 0);
        dist[n] = va[n];
        que.push_back(n), inq[n] = 1;
    } else {
        fill(&dist[1], &dist[n] + 1, 1e9);
        dist[1] = va[1];
        que.push_back(1), inq[1] = 1;
    }

    while (!que.empty()) {
        auto u = que.front(); que.pop_front();
        inq[u] = 0;

        for (int i = hh[u]; ~i; i = ne[i]) {
            int v = g[i];

            int flag = !type ? dist[v] > min(dist[u], va[v]) : dist[v] < max(dist[u], va[v]);
            if (flag) {
                if (!type) dist[v] = min(dist[u], va[v]);
                else dist[v] = max(dist[u], va[v]);

                if (inq[v]) continue;
                inq[v] = 1;
                int tmp = !type ? dist[v] < dist[que.front()] : dist[v] > dist[que.front()];
                if (!que.empty() && tmp) que.push_front(v);
                else que.push_back(v);
            }
        }
    }
}

void solve() {
    spfa(h, dmi, 0);
    spfa(rh, dmx, 1);

    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, dmx[i] - dmi[i]);
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
        memset(h, -1, sizeof h), memset(rh, -1, sizeof rh);

        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= m; i++) {
            int u, v, t;
            cin >> u >> v >> t;
            add(h, u, v), add(rh, v, u);
            if (t == 2) add(h, v, u), add(rh, u, v);
        }

        solve();
    }

    return 0;
}