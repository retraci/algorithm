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
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;

// region dinic
template<int N, int M>
struct Flow {
    using flowt = int;
    using pif = std::pair<int, flowt>;
    const flowt INF = 1e9;

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

    const vector<int> qr_min_cut(int S, int T) {
        fill(vis, vis + n + 1, 0);
        dfs(S);

        vector<int> res;
        for (int i = 0; i < edm; i += 2) {
            int v = e[i].fi, u = e[i ^ 1].fi;
            if (vis[u] && !vis[v]) res.push_back(i);
        }

        return res;
    }
};
// endregion

const int N = 110;
const int M = 5010;

int n, m, S, T;
int a[N], b[N];
pii es[M];
Flow<2 * N, M + 2 * N> g;
int st[2 * N];

void init() {
    S = 2 * n + 1, T = 2 * n + 2;
    g.init(2 * n + 2);

    for (int i = 1; i <= n; i++) {
        g.add(S, i, a[i], 0);
        g.add(n + i, T, b[i], 0);
    }
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        g.add(v, n + u, 1e9, 0);
    }
}

void solve() {
    init();

    cout << g.max_flow(S, T) << "\n";
    auto &mine = g.qr_min_cut(S, T);

    vector<int> v1, v2;
    for (int eid : mine) {
        int u = g.e[eid ^ 1].fi, v = g.e[eid].fi;
        if (u == S) v1.push_back(v);
        if (v == T) v2.push_back(u);
    }

    int cnt = v1.size() + v2.size();
    cout << cnt << "\n";
    for (int x : v1) cout << x << " +" << "\n";
    for (int x : v2) cout << x - n << " -" << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            es[i] = {u, v};
        }
        solve();
    }

    return 0;
}