#include <bits/stdc++.h>

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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

// region e-dcc
template<int N, int M, class G>
struct EDcc {
    int n, m;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int co[N + 10], sz[N + 10], dcc;
    int br[2 * M + 10];

    EDcc() {}

    void init(int _n, int _m) {
        n = _n, m = _m, ti = 0, dcc = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
        fill(br, br + 2 * m + 1, 0);
    }

    // 重边合法 => pe, 重边不合法 => fno
    void tarjan(int u, int pe, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u);

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if ((i ^ 1) == pe) continue;

            if (!dfn[v]) {
                tarjan(v, i, g);
                low[u] = min(low[u], low[v]);

                if (low[v] > dfn[u]) br[i] = br[i ^ 1] = 1;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            dcc++;
            int t;
            do {
                t = stk.back(); stk.pop_back();
                co[t] = dcc;
                sz[dcc]++;
            } while (t != u);
        }
    }

    // 有重边
    G suodian(const G &g) {
        G res;
        res.init(dcc, 0);

        for (int u = 1; u <= n; u++) {
            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];
                if (co[u] == co[v]) continue;

                res.add(co[u], co[v]), res.add(co[v], co[u]);
            }
        }

        return res;
    }
};
// endregion

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 5010;
const int M = 10010;

using G = Graph<N, M>;

int n, m;
G g;
EDcc<N, M, G> edcc;

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!edcc.dfn[i]) edcc.tarjan(i, -1, g);
    }

    vector<int> du(edcc.dcc + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            if (edcc.br[i]) {
                int v = g.e[i];
                int cu = edcc.co[u], cv = edcc.co[v];
                du[cv]++;
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i <= edcc.dcc; i++) {
        cnt += du[i] == 1;
    }
    cout << (cnt + 1) / 2 << "\n";
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
//    cin >> T;
    while (_--) {
        cin >> n >> m;
        g.init(n, m);

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v), g.add(v, u);
        }

        solve();
    }

    return 0;
}