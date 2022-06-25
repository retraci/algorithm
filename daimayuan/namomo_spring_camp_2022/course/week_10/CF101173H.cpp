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
template<int N, class G>
struct Lca {
    using lcat = int;
    using pit = pair<int, lcat>;

    int n, mxb;
    int dep[N + 10], fa[__lg(N) + 1][N + 10];
    lcat w[__lg(N) + 1][N + 10];
    int *d;

    Lca() {}

    void init(int rt, const G &g, int *_d) {
        n = g.n, mxb = __lg(n), d = _d;
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1, fa[0][rt] = 0, w[0][rt] = 0;
        while (!que.empty()) {
            int u = que.front(); que.pop();

            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                auto [v, cost] = g.e[i];

                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    fa[0][v] = u, w[0][v] = min(d[u], d[v]);
                    que.push(v);
                }
            }
        }

        for (int k = 1; k <= mxb; k++) {
            for (int v = 1; v <= n; v++) {
                fa[k][v] = fa[k - 1][fa[k - 1][v]];
                w[k][v] = min(w[k - 1][v], w[k - 1][fa[k - 1][v]]);
            }
        }
    }

    pit lca(int x, int y) {
        lcat res = min(d[x], d[y]);
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) {
                res = min(res, w[k][x]);
                x = fa[k][x];
            }
        }
        if (x == y) return {x, res};

        for (int k = mxb; k >= 0; k--) {
            if (fa[k][x] != fa[k][y]) {
                res = min({res, w[k][x], w[k][y]});
                x = fa[k][x], y = fa[k][y];
            }
        }

        res = min({res, w[0][x], w[0][y]});
        return {fa[0][x], res};
    }
};
// endregion

// region 带权图
template<int N, int M>
struct Graph {
    using gt = int;
    using pit = pair<int, gt>;

    int n, m;
    pit e[M * 2 + 10];
    int h[N + 10], ne[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, gt cost) {
        e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1010;

using G = Graph<N * N, 2 * N * N>;

int n;
int d[N * N];
string a[N];
Dsu<N * N> dsu;
G g;
Lca<N * N, G> lca;

int get(int x, int y) {
    return (x - 1) * n + y;
}

void bfs() {
    queue<pii> que;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '#') que.push({i, j});
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
            if (a[nx][ny] == '.' && !d[v]) {
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
            if (a[i][j] == '#') continue;

            int u = get(i, j);
            if (i + 1 <= n && a[i + 1][j] == '.') {
                int v = get(i + 1, j);

                int cost = min(d[u], d[v]);
                es.push_back({u, v, cost});
            }
            if (j + 1 <= n && a[i][j + 1] == '.') {
                int v = get(i, j + 1);

                int cost = min(d[u], d[v]);
                es.push_back({u, v, cost});
            }
        }
    }

    sort(es.begin(), es.end(), [](auto &a, auto &b) {
        return get<2>(a) > get<2>(b);
    });

    g.init(n * n + 1, -1);
    dsu.init(n * n + 1);
    for (auto [u, v, cost] : es) {
        if (dsu.unite(u, v)) {
            int x1 = (u - 1) / n + 1, y1 = (u - 1) % n + 1;
            int x2 = (v - 1) / n + 1, y2 = (v - 1) % n + 1;

            g.add(u, v, 0), g.add(v, u, 0);
        }
    }

    for (int i = 1; i <= n * n; i++) {
        int x = (i - 1) / n + 1, y = (i - 1) % n + 1;
        if (i == dsu.find(i) && a[x][y] == '.') {
            g.add(n * n + 1, i, 0);
        }
    }

    lca.init(n * n + 1, g, d);
}

void solve() {
    init();

    int q;
    cin >> q;
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int u = get(x1, y1), v = get(x2, y2);
        cout << lca.lca(u, v).se << "\n";
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
            cin >> a[i];
            a[i] = ' ' + a[i];
        }
        solve();
    }

    return 0;
}