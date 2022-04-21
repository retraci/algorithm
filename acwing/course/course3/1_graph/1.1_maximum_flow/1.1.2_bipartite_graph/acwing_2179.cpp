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

const int N = 155;
const int M = 277;

int n, m;
int a[N], b[M];

int tt, sc, sk;
pii e[2 * (N * M + N + M)];
int h[N + M], ne[2 * (N * M + N + M)], edm;
int nh[N + M], d[N + M];

void add(int u, int v, int cap) {
    e[edm] = {v, cap};
    ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, 0};
    ne[edm] = h[v], h[v] = edm++;
}

bool bfs() {
    vector<int> vis(tt + 1);
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

void init() {
    tt = n + m + 2;
    sc = tt - 1, sk = tt;

    fill(h, h + tt + 1, -1), edm = 0;
    for (int i = 1; i <= n; i++) add(sc, i, a[i]);
    for (int i = 1; i <= m; i++) add(i + n, sk, b[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            add(i, n + j, 1);
        }
    }
}

void solve() {
    init();

    int nd = accumulate(a + 1, a + n + 1, 0);
    int ret = dinic();
    if (nd != ret) {
        cout << 0 << "\n";
        return;
    }

    cout << 1 << "\n";
    for (int u = 1; u <= n; u++) {
        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];
            if (cap == 0) {
                cout << v - n << " ";
            }
        }
        cout << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) cin >> b[i];
        solve();
    }

    return 0;
}