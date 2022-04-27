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

const int N = 510;
const int M = 3010 + 2 * N;

// region dinic 整数
int n, m, S, T;
pii e[2 * M];
int h[N], ne[2 * M], edm;
int d[N], nh[N], tt;

void add(int u, int v, int c1, int c2) {
    e[edm] = {v, c1}, ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, c2}, ne[edm] = h[v], h[v] = edm++;
}

bool bfs() {
    fill(d + 1, d + tt + 1, -1);
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

int dfs(int u, int lit) {
    if (u == T) return lit;

    int flow = 0;
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
        int tmp;
        while (tmp = dfs(S, 1e9)) flow += tmp;
    }
    return flow;
}
// endregion

int k;
int a[N];
pii es[M];

ll work(int x) {
    fill(h, h + tt + 1, -1), edm = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) continue;

        if (a[i] >> x & 1) add(S, i, 1e9, 0);
        else add(i, T, 1e9, 0);
    }
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        add(u, v, 1, 1);
    }

    return (1 << x) * dinic();
}

void solve() {
    tt = n + 2;
    S = tt - 1, T = tt;

    ll ans = 0;
    for (int i = 0; i <= 30; i++) ans += work(i);
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
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            es[i] = {u, v};
        }

        fill(a, a + n + 1, -1);
        cin >> k;
        for (int i = 1; i <= k; i++) {
            int u, x;
            cin >> u >> x;
            a[u] = x;
        }

        solve();
    }

    return 0;
}