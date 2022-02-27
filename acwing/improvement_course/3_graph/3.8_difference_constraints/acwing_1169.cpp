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
const int M = 3e5 + 10;

int n, m;
pii g[M];
int ne[M], h[N], edm;

ll dist[N], st[N], cnt[N];

void add(int u,int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void init() {
    for (int i = 1; i <= n; i++) add(0, i, 1);
}

bool spfa() {
    vector<int> que;
    dist[0] = 0;
    que.push_back(0), st[0] = 1;
    while (!que.empty()) {
        auto u = que.back(); que.pop_back();
        st[u] = 0;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v] < dist[u] + cost) {
                dist[v] = dist[u] + cost;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1) return false;

                if (!st[v]) {
                    st[v] = 1;
                    que.push_back(v);
                }
            }
        }
    }

    return true;
}

void solve() {
    init();

    if (!spfa()) {
        cout << -1 << "\n";
        return;
    }

    ll ans = accumulate(&dist[1], &dist[n] + 1, 0LL);
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
        fill(h, h + n + 1, -1), edm = 0;

        while (m--) {
            int x, u, v;
            cin >> x >> u >> v;
            if (x == 1) add(u, v, 0), add(v, u, 0);
            else if (x == 2) add(u, v, 1);
            else if (x == 3) add(v, u, 0);
            else if (x == 4) add(v, u, 1);
            else add(u, v, 0);
        }
        solve();
    }

    return 0;
}