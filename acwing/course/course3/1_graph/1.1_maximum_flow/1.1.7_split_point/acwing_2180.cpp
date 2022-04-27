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

const int N = 2 * 500 + 10;
const int M = N * N;

// region dinic
int n, m, S, T;
pii e[2 * M];
int h[N], ne[2 * M], edm;
int d[N], nh[N], tt;

void add(int u, int v, int cap) {
    e[edm] = {v, cap}, ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, 0}, ne[edm] = h[v], h[v] = edm++;
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

int a[N];
int f[N];
int s, sum;

void work1() {
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] <= a[i]) f[i] = max(f[i], f[j] + 1);
        }
    }

    s = *max_element(f + 1, f + n + 1);
    cout << s << "\n";
}

void work2() {
    tt = 2 * n + 2;
    fill(h, h + tt + 1, -1), edm = 0;

    S = tt - 1, T = tt;
    for (int i = 1; i <= n; i++) {
        if (f[i] == 1) add(S, i, 1);
        if (f[i] == s) add(n + i, T, 1);
    }
    for (int i = 1; i <= n; i++) add(i, n + i, 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] <= a[i] && f[i] == f[j] + 1) add(n + j, i, 1);
        }
    }

    sum = dinic();
    cout << sum << "\n";
}

void work3() {
    for (int i = 0; i < edm; i += 2) {
        int u = e[i ^ 1].fi;
        auto &[v, cap] = e[i];

        if (u == 1 && v == n + 1) cap = 1e9;
        if (u == n && v == n + n) cap = 1e9;

        if (u == S && v == 1) cap = 1e9;
        if (u == n + n && v == T) cap = 1e9;
    }

    sum += dinic();
    cout << sum << "\n";
}

void solve() {
    work1();
    if (n == 1) {
        cout << n << "\n";
        cout << n << "\n";
        return;
    }

    work2();
    work3();
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}