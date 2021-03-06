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

const int N = 10010;
const int M = 1e5 + 10;

int n, m, S, T;
int s[N], t[N], sc, tc;
ti3 es[M];
pll e[2 * (M + N)];
int h[N], ne[2 * (M + N)], edm;
int d[N], nh[N], tt;

void add(int u, int v, ll cap) {
    e[edm] = {v, cap};
    ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, 0};
    ne[edm] = h[v], h[v] = edm++;
}

bool bfs() {
    fill(d, d + tt + 1, -1);
    queue<int> que;
    d[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];
            if (d[v] != -1 || cap == 0) continue;

            d[v] = d[u] + 1;
            if (v == T) return true;
            que.push(v);
        }
    }

    return false;
}

ll dfs(int u, ll lit) {
    if (u == T) return lit;

    ll flow = 0;
    for (int &i = nh[u]; ~i; i = ne[i]) {
        auto &[v, cap] = e[i];
        if (d[v] != d[u] + 1 || cap == 0) continue;

        int ret = dfs(v, min(cap, lit - flow));
        if (ret == 0) d[v] = -1;
        flow += ret, cap -= ret, e[i ^ 1].se += ret;

        if (lit - flow == 0) break;
    }
    return flow;
}

ll dinic() {
    ll flow = 0;
    while (bfs()) {
        for (int i = 1; i <= tt; i++) nh[i] = h[i];
        ll tmp;
        while (tmp = dfs(S, 1e18)) flow += tmp;
    }
    return flow;
}

void init() {
    tt = n + 2;
    S = tt - 1, T = tt;
    fill(h, h + tt + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [u, v, cap] = es[i];
        add(u, v, cap);
    }

    for (int i = 1; i <= sc; i++) add(S, s[i], 1e18);
    for (int i = 1; i <= tc; i++) add(t[i], T, 1e18);
}

void solve() {
    init();

    cout << dinic() << "\n";
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m >> sc >> tc;
        for (int i = 1; i <= sc; i++) cin >> s[i];
        for (int i = 1; i <= tc; i++) cin >> t[i];
        for (int i = 1; i <= m; i++) {
            int u, v, cap;
            cin >> u >> v >> cap;
            es[i] = {u, v, cap};
        }
        solve();
    }

    return 0;
}