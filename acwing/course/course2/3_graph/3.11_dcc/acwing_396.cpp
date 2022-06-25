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

// region v-dcc
template<int N, class G>
struct VDcc {
    int n;
    int dfn[N + 10], low[N + 10], ti, rt;
    vector<int> stk;
    vector<int> cc[N + 10];
    int cut[N + 10], dcc;

    void init(int _n) {
        n = _n, ti = 0, dcc = 0;
        fill(dfn, dfn + n + 1, 0);
        for (int i = 1; i <= n; i++) cc[i].clear();
        fill(cut, cut + n + 1, 0);
    }

    // 由于判割点, tarjan前给rt赋值: tarjan(g.rt = u, -1);
    // 重边合法 => pe, 重边不合法 => fno
    void tarjan(int u, int pe, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u);

        if (u == rt && g.h[u] == -1) {
            dcc++;
            cc[dcc].push_back(u);
            return;
        }

        int cnt = 0;
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if ((i ^ 1) == pe) continue;

            if (!dfn[v]) {
                tarjan(v, i, g);
                low[u] = min(low[u], low[v]);

                if (low[v] >= dfn[u]) {
                    if (++cnt >= 2 || u != rt) cut[u] = 1;

                    dcc++;
                    int t;
                    do {
                        t = stk.back(); stk.pop_back();
                        cc[dcc].push_back(t);
                    } while (t != v);
                    cc[dcc].push_back(u);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 510;
const int M = 1010;

using G = Graph<N, M>;
using ull = unsigned long long;

int n, m, Ca;
vector<pii> es;
G g;
VDcc<N, G> vdcc;

void init() {
    g.init(n, m);
    for (auto [u, v] : es) {
        g.add(u, v), g.add(v, u);
    }
}

void solve() {
    init();

    vdcc.init(n);
    for (int i = 1; i <= n; i++) {
        if (!vdcc.dfn[i]) {
            vdcc.tarjan(vdcc.rt = i, -1, g);
        }
    }

    ull ans1 = 0, ans2 = 1;
    for (int k = 1; k <= vdcc.dcc; k++) {
        int c = 0;
        for (int x : vdcc.cc[k]) {
            c += vdcc.cut[x];
        }

        int sz = vdcc.cc[k].size();
        if (c == 0) {
            if (sz == 1) ans1 += 1;
            else ans1 += 2, ans2 *= sz * (sz - 1) / 2;
        } else if (c == 1) {
            ans1 += 1, ans2 *= sz - 1;
        }
    }

    cout << "Case " << ++Ca << ": " << ans1 << " " << ans2 << "\n";
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
    while (cin >> m, m) {
        n = 0;
        es.clear();
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            es.push_back({u, v});
            n = max({n, u, v});
        }
        solve();
    }

    return 0;
}