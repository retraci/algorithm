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
const int M = 410;
const double eps = 1e-5;

// region dinic 浮点
using pid = std::pair<int, double>;

int n, m, S, T;
pid e[2 * M];
int h[N], ne[2 * M], edm;
int d[N], nh[N], tt;

void add(int u, int v, double cap) {
    e[edm] = {v, cap}, ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, cap}, ne[edm] = h[v], h[v] = edm++;
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

double dfs(int u, double lit) {
    if (u == T) return lit;

    double flow = 0;
    for (int &i = nh[u]; ~i; i = ne[i]) {
        auto &[v, cap] = e[i];
        if (d[v] != d[u] + 1 || cap == 0) continue;

        double ret = dfs(v, min(cap, lit - flow));
        if (ret == 0) d[v] = -1;
        flow += ret, cap -= ret, e[i ^ 1].se += ret;

        if (lit - flow == 0) break;
    }

    return flow;
}

double dinic() {
    double flow = 0;
    while (bfs()) {
        for (int i = 1; i <= tt; i++) nh[i] = h[i];
        double tmp;
        while (tmp = dfs(S, 1e9)) flow += tmp;
    }
    return flow;
}
// endregion

ti3 es[M];

void init() {
    tt = n;
    fill(h, h + tt + 1, -1), edm = 0;

    for (int i = 1; i <= m; i++) {
        auto [u, v, cap] = es[i];

        add(u, v, cap);
    }
}

bool check(double md) {
    double sum = 0;
    for (int i = 0; i < edm; i += 2) {
        int cap = get<2>(es[i / 2 + 1]);
        if (cap - md <= 0) {
            sum += cap - md;
            e[i].se = e[i ^ 1].se = 0;
        } else {
            e[i].se = e[i ^ 1].se = cap - md;
        }
    }

    sum += dinic();
    return sum < 0;
}

void solve() {
    init();

    double left = 0, right = 1e7;
    while (left + eps < right) {
        double md = (left + right) / 2;
        if (check(md)) right = md;
        else left = md;
    }

    cout << fixed << setprecision(2);
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
        cin >> n >> m >> S >> T;
        for (int i = 1; i <= m; i++) {
            int u, v, cap;
            cin >> u >> v >> cap;
            es[i] = {u, v, cap};
        }

        solve();
    }

    return 0;
}