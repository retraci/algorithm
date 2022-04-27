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

using ai3 = array<int, 3>;

const int N = 210;
const int M = 40010;

int n, m, k, S, T;
ai3 e[2 * M];
int h[N], ne[2 * M], edm;
int d[N], nh[N];

void add(int u, int v, int cap, int len) {
    e[edm] = {v, cap, len}, ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, cap, len}, ne[edm] = h[v], h[v] = edm++;
}

bool bfs(int md) {
    fill(d, d + n + 1, -1);
    queue<int> que;
    d[S] = 0;
    que.push(S);
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap, len] = e[i];
            if (cap == 0 || d[v] != -1 || len > md) continue;

            d[v] = d[u] + 1;
            if (v == T) return true;
            que.push(v);
        }
    }

    return false;
}

int dfs(int u, int lit, int md) {
    if (u == T) return lit;

    int flow = 0;
    for (int &i = nh[u]; ~i; i = ne[i]) {
        auto &[v, cap, len] = e[i];
        if (cap == 0 || d[v] != d[u] + 1 || len > md) continue;

        int ret = dfs(v, min(cap, lit - flow), md);
        if (ret == 0) d[v] = -1;
        flow += ret, cap -= ret, e[i ^ 1][1] += ret;

        if (lit - flow == 0) break;
    }

    return flow;
}

int dinic(int md) {
    int flow = 0;
    while (bfs(md)) {
        for (int i = 1; i <= n; i++) nh[i] = h[i];
        int tmp;
        while (tmp = dfs(S, 1e9, md)) flow += tmp;
    }
    return flow;
}

bool check(int md) {
    for (int i = 0; i < edm; i++) e[i][1] = 1;
    return dinic(md) >= k;
}

void solve() {
    S = 1, T = n;

    int left = 1, right = 1e6;
    while (left < right) {
        int md = left + right >> 1;
        if (check(md)) right = md;
        else left = md + 1;
    }

    cout << left << "\n";
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
        cin >> n >> m >> k;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v, len;
            cin >> u >> v >> len;
            add(u, v, 1, len);
        }
        solve();
    }

    return 0;
}