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
    void tarjan(int u, int pe, const G &g, int &mx) {
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
                tarjan(v, i, g, mx);
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

        if (u == rt) mx = max(mx, cnt);
        else mx = max(mx, cnt + 1);
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 10010;
const int M = 15010;

using G = Graph<N, M>;

int n, m;
G g;
VDcc<N, G> vdcc;

void solve() {
    int mx = 0;
    int cnt = 0;

    vdcc.init(n);
    for (int i = 1; i <= n; i++) {
        if (!vdcc.dfn[i]) {
            cnt++;
            vdcc.tarjan(vdcc.rt = i, -1, g, mx);
        }
    }

    int ans = cnt + mx - 1;
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
    int T = 1;
//    cin >> T;
    while (cin >> n >> m, n || m) {
        g.init(n, m);

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            u++, v++;
            g.add(u, v), g.add(v, u);
        }

        solve();
    }

    return 0;
}