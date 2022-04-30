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

// region dinic 整数
template<int N, int M>
struct Dinic {
    int n, m, S, T;
    pii e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int d[N + 10], nh[N + 10], vis[N + 10];

    Dinic() {}

    void init(int _n, int _S, int _T) {
        n = _n, S = _S, T = _T;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, int c1, int c2) {
        e[edm] = {v, c1}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, c2}, ne[edm] = h[v], h[v] = edm++;
    }

    bool bfs() {
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
            for (int i = 1; i <= n; i++) nh[i] = h[i];
            int tmp;
            while (tmp = dfs(S, 1e9)) flow += tmp;
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

    const array<vector<int>, 2> qr() {
        fill(vis, vis + n + 1, 0);
        dfs(S);

        array<vector<int>, 2> res;
        for (int i = 0; i < edm; i += 2) {
            int v = e[i].fi, u = e[i ^ 1].fi;
            if (vis[u] && !vis[v]) {
                if (u == S) res[0].push_back(v);
            }
        }
        for (int i = 0; i < edm; i += 2) {
            int v = e[i].fi, u = e[i ^ 1].fi;
            if (vis[u] && !vis[v]) {
                if (v == T) res[1].push_back(u);
            }
        }

        return res;
    }
};
// endregion

const int N = 55;
const int M = N * N / 2;

int n, m;
pii es[M];
Dinic<N * 2, 2 * M + N> g;

void init() {
    int tt = 2 * n;
    g.init(tt, -1, -1);

    for (int i = 1; i <= n; i++) g.add(i, n + i, 1, 0);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];

        g.add(n + u, v, 1e9, 0);
        g.add(n + v, u, 1e9, 0);
    }
}

void solve() {
    init();

    ll ans = n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            g.S = n + i, g.T = j;
            for (int k = 0; k < g.edm; k += 2) {
                g.e[k].se += g.e[k ^ 1].se;
                g.e[k ^ 1].se = 0;
            }

            ans = min(ans, g.dinic());
        }
    }

    printf("%lld\n", ans);
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
//    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf(" (%d,%d)", &u, &v);
            u++, v++;
            es[i] = {u, v};
        }
        solve();
    }

    return 0;
}