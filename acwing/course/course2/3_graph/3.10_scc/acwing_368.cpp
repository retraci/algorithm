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

// region 有边权 scc
template<int N, class G>
struct Tarjan {
    int n;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int ins[N + 10];
    int co[N + 10], sz[N + 10], scc;

    Tarjan() {}

    void init(int _n) {
        n = _n, ti = 0, scc = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }

    void tarjan(int u, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u), ins[u] = 1;

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            auto [v, cost] = g.e[i];

            if (!dfn[v]) {
                tarjan(v, g);
                low[u] = min(low[u], low[v]);
            } else if (ins[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            scc++;
            int t;
            do {
                t = stk.back(); stk.pop_back(); ins[t] = 0;
                co[t] = scc;
                sz[scc]++;
            } while (t != u);
        }
    }

    pair<G, int> suodian(const G &g) {
        G res;
        res.init(scc, -1);
        int flag = 0;
        for (int u = 1; u <= n; u++) {
            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                auto [v, cost] = g.e[i];
                if (co[u] == co[v]) {
                    flag |= cost > 0;
                    continue;
                }

                res.add(co[u], co[v], cost);
            }
        }

        return {res, flag};
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
const int N = 1e5 + 10;
const int M = 3e5 + 10;

using G = Graph<N, M>;

int n, m;
G g;
Tarjan<N, G> tj;

void solve() {
    for (int i = 1; i <= n; i++) g.add(n + 1, i, 1);

    tj.init(n + 1);
    for (int i = 1; i <= n + 1; i++) {
        if (!tj.dfn[i]) tj.tarjan(i, g);
    }

    auto [ng, flag] = tj.suodian(g);
    int scc = tj.scc;
    if (flag) {
        cout << -1 << "\n";
        return;
    }

    vector<ll> f(scc + 1, 0);
    for (int u = scc; u >= 1; u--) {
        for (int i = ng.h[u]; ~i; i = ng.ne[i]) {
            auto [v, cost] = ng.e[i];
            f[v] = max(f[v], f[u] + cost);
        }
    }

    ll ans = 0;
    for (int i = 1; i <= scc; i++) ans += tj.sz[i] * f[i];
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
        g.init(n + 1, m);

        while (m--) {
            int x, u, v;
            cin >> x >> u >> v;
            if (x == 1) g.add(u, v, 0), g.add(v, u, 0);
            else if (x == 2) g.add(u, v, 1);
            else if (x == 3) g.add(v, u, 0);
            else if (x == 4) g.add(v, u, 1);
            else g.add(u, v, 0);
        }
        solve();
    }

    return 0;
}