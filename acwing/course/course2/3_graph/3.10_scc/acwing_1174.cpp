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

// region 无边权 scc
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
            int v = g.e[i];

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

    vector<int> suodian(const G &g) {
        vector<int> res(scc + 1);

        for (int u = 1; u <= n; u++) {
            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];
                if (co[u] == co[v]) continue;

                res[co[u]]++;
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
const int N = 1e4 + 10;
const int M = 5e4 + 10;

using G = Graph<N, M>;

int n, m;
G g;
Tarjan<N, G> tj;

void solve() {
    tj.init(n);
    for (int i = 1; i <= n; i++) {
        if (!tj.dfn[i]) tj.tarjan(i, g);
    }

    vector<int> du = tj.suodian(g);
    int cnt = 0;
    for (int i = 1; i <= tj.scc; i++) cnt += du[i] == 0;
    if (cnt > 1) {
        cout << 0 << "\n";
        return;
    }
    int id = min_element(du.begin() + 1, du.end()) - du.begin();
    cout << tj.sz[id] << "\n";
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> m;
        g.init(n, m);

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v);
        }

        solve();
    }

    return 0;
}