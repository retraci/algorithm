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

const int N = 210;
const int dir[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};

int n, m;
int a[N][N];
Dinic<N * N, 4 * N * N + N * N> g;

int get(int x, int y) {
    return (x - 1) * n + (y - 1) + 1;
}

void init() {
    int tt = n * n + 2;
    g.init(tt, tt - 1, tt);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j]) continue;

            if (i + j & 1) {
                g.add(g.S, get(i, j), 1, 0);

                for (int k = 0; k < 8; k++) {
                    int nx = i + dir[k][0], ny = j + dir[k][1];
                    if (nx < 1 || nx > n || ny < 1 || ny > n) continue;

                    g.add(get(i, j), get(nx, ny), 1e9, 0);
                }
            } else {
                g.add(get(i, j), g.T, 1, 0);
            }
        }
    }
}

void solve() {
    init();

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum += !a[i][j];
        }
    }

    int ans = sum - g.dinic();
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
            a[u][v] = 1;
        }
        solve();
    }

    return 0;
}