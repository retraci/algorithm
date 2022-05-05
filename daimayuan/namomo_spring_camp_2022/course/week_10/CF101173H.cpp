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
using ai3 = array<int, 3>;

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

// region 边权lca
template<int N, int M>
struct Lca {
    using pll = pair<ll, ll>;
    int n, mxb;
    int *d;
    int e[M * 2 + 10];
    int h[N + 10], ne[M * 2 + 10], edm;
    int dep[N + 10], fa[N + 10][32];
    ll w[N + 10][32];

    Lca() {}

    void init(int _n, int *_d) {
        n = _n, d = _d, mxb = __lg(n);
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void init_lca(int rt) {
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        dep[0] = 0, dep[rt] = 1;
        que.push(rt);
        while (!que.empty()) {
            int u = que.front(); que.pop();

            for (int i = h[u]; ~i; i = ne[i]) {
                int v = e[i];

                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    fa[v][0] = u, w[v][0] = min(d[u], d[v]);
                    que.push(v);

                    for (int k = 1; k <= mxb; k++) {
                        fa[v][k] = fa[fa[v][k - 1]][k - 1];
                        w[v][k] = min(w[v][k - 1], w[fa[v][k - 1]][k - 1]);
                    }
                }
            }
        }
    }

    pll work(int x, int y) {
        ll res = min(d[x], d[y]);
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[x][k]] >= dep[y]) {
                res = min(res, w[x][k]);
                x = fa[x][k];
            }
        }
        if (x == y) return {x, res};

        for (int k = mxb; k >= 0; k--) {
            if (fa[x][k] != fa[y][k]) {
                res = min({res, w[x][k], w[y][k]});
                x = fa[x][k], y = fa[y][k];
            }
        }
        res = min({res, w[x][0], w[y][0]});
        return {fa[x][0], res};
    }

};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1010;
const int M = 2 * N * N;

int n;
int d[N * N];
string g[N];
Dsu<N * N> dsu;
Lca<N * N, M> lca;

int get(int x, int y) {
    return (x - 1) * n + y;
}

void bfs() {
    queue<pii> que;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] == '#') que.push({i, j});
        }
    }
    for (int i = 0; i <= n + 1; i++) que.push({i, 0}), que.push({i, n + 1});
    for (int j = 0; j <= n + 1; j++) que.push({0, j}), que.push({n + 1, j});

    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();
        int u = (x < 1 || x > n || y < 1 || y > n) ? 0 : get(x, y);

        for (int k = 0; k < 8; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;

            int v = get(nx, ny);
            if (g[nx][ny] == '.' && !d[v]) {
                d[v] = d[u] + 1;
                que.push({nx, ny});
            }
        }
    }
}

void init() {
    bfs();
    for (int i = 1; i <= n * n; i++) d[i] = (d[i] - 1) * 2 + 1;

    vector<ai3> es;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] == '#') continue;

            int u = get(i, j);
            if (i + 1 <= n && g[i + 1][j] == '.') {
                int v = get(i + 1, j);

                int cost = min(d[u], d[v]);
                es.push_back({u, v, cost});
            }
            if (j + 1 <= n && g[i][j + 1] == '.') {
                int v = get(i, j + 1);

                int cost = min(d[u], d[v]);
                es.push_back({u, v, cost});
            }
        }
    }

    sort(es.begin(), es.end(), [](auto &a, auto &b) {
        return get<2>(a) > get<2>(b);
    });

    lca.init(n * n + 1, d);
    dsu.init(n * n + 1);
    for (auto [u, v, cost] : es) {
        if (dsu.unite(u, v)) {
            int x1 = (u - 1) / n + 1, y1 = (u - 1) % n + 1;
            int x2 = (v - 1) / n + 1, y2 = (v - 1) % n + 1;

            lca.add(u, v), lca.add(v, u);
        }
    }

    for (int i = 1; i <= n * n; i++) {
        int x = (i - 1) / n + 1, y = (i - 1) % n + 1;
        if (i == dsu.find(i) && g[x][y] == '.') {
            lca.add(n * n + 1, i);
        }
    }

    lca.init_lca(n * n + 1);
}

void solve() {
    init();

    int q;
    cin >> q;
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int u = get(x1, y1), v = get(x2, y2);
        cout << lca.work(u, v).se << "\n";
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}