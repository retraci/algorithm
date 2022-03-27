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

const int N = 50010;
const int M = 3 * N;

int n, m;
pii g[M];
int ne[M], h[N], edm;

int dist[N], st[N];

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void init() {
    n = 50001;
    for (int i = 1; i <= n; i++) {
        add(i - 1, i, 0);
        add(i, i - 1, -1);
    }
}

bool spfa() {
    fill(dist, dist + n + 1, -1e9), fill(st, st + n + 1, 0);
    deque<int> que;
    dist[0] = 0;
    que.push_back(0), st[0] = 1;

    while (!que.empty()) {
        auto u = que.front(); que.pop_front();
        st[u] = 0;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v] < dist[u] + cost) {
                if (dist[u] != -1e9) dist[v] = dist[u] + cost;

                if (!st[v]) {
                    st[v] = 1;
                    if (!que.empty() && dist[v] < dist[que.front()]) que.push_front(v);
                    else que.push_back(v);
                }
            }
        }
    }

    return true;
}

void solve() {
    init();

    spfa();

    cout << dist[n] << "\n";
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
        cin >> m;
        memset(h, -1, sizeof h), edm = 0;

        while (m--) {
            int a, b, c;
            cin >> a >> b >> c;
            a++, b++;
            add(a - 1, b, c);
        }

        solve();
    }

    return 0;
}