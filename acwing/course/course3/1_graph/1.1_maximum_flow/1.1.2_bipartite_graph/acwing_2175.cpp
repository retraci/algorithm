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

const int N = 110;
const int M = N * N;

int n, m, sc, sk;
int ec, tt;
pii es[M];

pii e[2 * (M + 2 * N)];
int h[2 * N], ne[2 * (M + 2 * N)], edm;
int nh[2 * N], d[2 * N];

void add(int u, int v, int cap) {
    e[edm] = {v, cap};
    ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, 0};
    ne[edm] = h[v], h[v] = edm++;
}

void init() {
    tt = n + m + 2;
    sc = tt - 1, sk = tt;
    fill(h, h + n + m + 2 + 1, -1), edm = 0;

    for (int i = 1; i <= ec; i++) {
        auto [u, v] = es[i];
        add(u, v, 1);
    }

    for (int i = 1; i <= n; i++) add(sc, i, 1);
    for (int i = 1; i <= m; i++) add(n + i, sk, 1);
}

bool bfs() {
    vector<int> vis(tt + 1, 0);
    queue<int> que;
    vis[sc] = 1, d[sc] = 0;
    que.push(sc);
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];
            if (vis[v] || cap == 0) continue;
            vis[v] = 1;

            d[v] = d[u] + 1;
            if (v == sk) return true;
            que.push(v);
        }
    }

    return false;
}

int dfs(int u, int lit) {
    if (u == sk) return lit;

    int flow = 0;
    for (int &i = nh[u]; ~i; i = ne[i]) {
        auto &[v, cap] = e[i];
        if (d[v] != d[u] + 1 || cap == 0) continue;

        int t = dfs(v, min(lit - flow, cap));
        if (t == 0) d[v] = -1;
        flow += t, cap -= t, e[i ^ 1].se += t;

        if (flow == lit) break;
    }

    return flow;
}

int dinic() {
    int flow = 0;
    while (bfs()) {
        for (int i = 1; i <= tt; i++) nh[i] = h[i];
        int tmp;
        while (tmp = dfs(sc, 1e9)) flow += tmp;
    }
    return flow;
}

void solve() {
    init();

    cout << dinic() << "\n";
    for (int i = 0; i < edm; i += 2) {
        auto [v, cap] = e[i];
        if (cap == 0 && v > n && v <= n + m) {
            cout << e[i ^ 1].fi << " " << v << "\n";
        }
    }
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

        int u, v;
        while (cin >> u >> v, u != -1) {
            es[++ec] = {u, v};
        }
        solve();
    }

    return 0;
}