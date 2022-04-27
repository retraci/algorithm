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

const int N = 17;
const int M = 23;
const int D = 1210;

// region dinic
int n, m, S, T;
pii e[2 * (D * (M + N) + D)];
int h[D * N], ne[2 * (D * (M + N) + D)], edm;
int d[D * N], nh[D * N], tt;

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

// region dsu
template <int SZ>
struct Dsu {
    int pa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(pa, pa + _n + 1, 0);
    }

    int find(int x) {
        return x == pa[x] ? x : pa[x] = find(pa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        pa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

int k;
int a[M];
vector<int> b[M];
Dsu<33> dsu;

int get(int day, int u) {
    return 2 + day * (n + 2) + u;
}

void solve() {
    dsu.init(n + 2);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j < b[i].size(); j++) {
            int u = b[i][j - 1], v = b[i][j];
            dsu.unite(u, v);
        }
    }

    if (!dsu.same(n + 1, n + 2)) {
        cout << 0 << "\n";
        return;
    }

    edm = 0;
    S = 1, T = 2;
    tt = get(0, n + 2);
    fill(h, h + tt + 1, -1);
    add(S, get(0, n + 1), k);
    add(get(0, n + 2), T, 1e9);
    int day = 0, s = 0;
    while (1) {
        day++;

        fill(h + tt + 1, h + tt + n + 2 + 1, -1);
        tt += n + 2;
        add(get(day, n + 2), T, 1e9);
        for (int i = 1; i <= n + 2; i++) add(get(day - 1, i), get(day, i), 1e9);
        for (int i = 1; i <= m; i++) {
            int r = b[i].size();
            int u = b[i][(day - 1) % r], v = b[i][day % r];
            add(get(day - 1, u), get(day, v), a[i]);
        }

        int t = dinic();
        s += t;
        if (s >= k) break;
    }

    cout << day << "\n";
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

        for (int i = 1; i <= m; i++) {
            cin >> a[i];
            int r;
            cin >> r;
            while (r--) {
                int t;
                cin >> t;
                if (t == 0) t = n + 1;
                if (t == -1) t = n + 2;
                b[i].push_back(t);
            }
        }
        solve();
    }

    return 0;
}