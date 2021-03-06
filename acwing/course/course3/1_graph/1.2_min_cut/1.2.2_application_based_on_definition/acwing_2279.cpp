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

// region dinic
template<int N, int M>
struct Flow {
    using flowt = double;
    using pif = std::pair<int, flowt>;
    const flowt INF = 1e18;

    int n;
    pif e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int d[N + 10], nh[N + 10], vis[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt c1, flowt c2) {
        e[edm] = {v, c1}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, c2}, ne[edm] = h[v], h[v] = edm++;
    }

    bool bfs(int S, int T) {
        fill(d + 1, d + n + 1, -1);
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

    flowt dfs(int u, int T, flowt lit) {
        if (u == T) return lit;

        flowt flow = 0;
        for (int &i = nh[u]; ~i; i = ne[i]) {
            auto &[v, cap] = e[i];
            if (d[v] != d[u] + 1 || cap == 0) continue;

            flowt ret = dfs(v, T, min(cap, lit - flow));
            if (ret == 0) d[v] = -1;
            flow += ret, cap -= ret, e[i ^ 1].se += ret;

            if (lit - flow == 0) break;
        }

        return flow;
    }

    flowt max_flow(int S, int T) {
        flowt flow = 0;
        while (bfs(S, T)) {
            for (int i = 1; i <= n; i++) nh[i] = h[i];
            while (1) {
                flowt t = dfs(S, T, INF);
                if (t == 0) break;

                flow += t;
            }
        }
        return flow;
    }

    void dfs(int u) {
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];

            if (!vis[v] && cap) dfs(v);
        }
    }

    const array<vector<int>, 2> qr(int S, int T) {
        fill(vis, vis + n + 1, 0);
        dfs(S);

        array<vector<int>, 2> res;
        for (int i = 0; i < edm; i += 2) {
            int v = e[i].fi, u = e[i ^ 1].fi;
            if (vis[u] && !vis[v]) {
                if (u == S) res[0].push_back(v);
                if (v == T) res[1].push_back(u);
            }
        }

        return res;
    }
};
// endregion

int n, m, S, T;
ti3 es[M];
Flow<N, M> g;

void init() {
    g.init(n);

    for (int i = 1; i <= m; i++) {
        auto [u, v, cap] = es[i];

        g.add(u, v, cap, cap);
    }
}

bool check(double md) {
    double sum = 0;
    for (int i = 0; i < g.edm; i += 2) {
        int cap = get<2>(es[i / 2 + 1]);
        if (cap - md <= 0) {
            sum += cap - md;
            g.e[i].se = g.e[i ^ 1].se = 0;
        } else {
            g.e[i].se = g.e[i ^ 1].se = cap - md;
        }
    }

    sum += g.max_flow(S, T);
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