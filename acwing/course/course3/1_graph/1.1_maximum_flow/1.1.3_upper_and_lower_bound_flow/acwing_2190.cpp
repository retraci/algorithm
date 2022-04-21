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

const int N = 50013;
const int M = 125013;

int n, m, s, t, S, T, tt;
ti4 es[M];
pll e[2 * (M + N)];
int h[N], ne[2 * (M + N)], edm;
int d[N], nh[N];
ll a[N], nd;

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
        auto u = que.front(); que.pop();

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

        ll ret = dfs(v, min(cap, lit - flow));
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
        auto [u, v, lb, rb] = es[i];
        add(u, v, rb - lb);
        a[u] += lb, a[v] -= lb;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) add(i, T, a[i]);
        if (a[i] < 0) add(S, i, -a[i]), nd += -a[i];
    }

    add(t, s, 1e18);
}

void solve() {
    init();

    ll ret = dinic();
    if (ret != nd) {
        cout << "No Solution" << "\n";
        return;
    }

    ll ans = e[edm - 1].se;
    e[edm - 1].se = e[edm - 2].se = 0;
    S = t, T = s;
    ans -= dinic();
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m >> s >> t;
        for (int i = 1; i <= m; i++) {
            int u, v, lb, rb;
            cin >> u >> v >> lb >> rb;
            es[i] = {u, v, lb, rb};
        }
        solve();
    }

    return 0;
}