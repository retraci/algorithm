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

// region 边权lca
template<int N, class G>
struct Lca {
    using lcat = int;
    using pit = pair<int, lcat>;

    int n, mxb;
    int dep[N + 10], fa[__lg(N) + 1][N + 10];
    lcat w[__lg(N) + 1][N + 10];

    Lca() {}

    void init(int rt, const G &g) {
        n = g.n, mxb = __lg(n);
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
                    fa[0][v] = u, w[0][v] = cost;
                    que.push(v);
                }
            }
        }

        for (int k = 1; k <= mxb; k++) {
            for (int v = 1; v <= n; v++) {
                fa[k][v] = fa[k - 1][fa[k - 1][v]];
                w[k][v] = w[k - 1][v] + w[k - 1][fa[k - 1][v]];
            }
        }
    }

    pit lca(int x, int y) {
        lcat res = 0;
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) {
                res += w[k][x];
                x = fa[k][x];
            }
        }
        if (x == y) return {x, res};

        for (int k = mxb; k >= 0; k--) {
            if (fa[k][x] != fa[k][y]) {
                res += w[k][x] + w[k][y];
                x = fa[k][x], y = fa[k][y];
            }
        }

        res += w[0][x] + w[0][y];
        return {fa[0][x], res};
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 5e5 + 10;

using G = Graph<N, N>;

int n;
map<pii, int> b;
G g, ng;
Lca<N, G> lca;
int siz[N], in[N], out[N], ti;
ll f[N][2], ans;

void pdfs(int u, int fno) {
    in[u] = ++ti;
    siz[u] = 1;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        auto [v, cost] = g.e[i];
        if (v == fno) continue;

        pdfs(v, u);
        siz[u] += siz[v];
    }

    out[u] = ti;
}

bool issub(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

void build(vector<int> &vs) {
    static vector<int> stk;
    static set<int> st;

    // 去重, 并把可能的lca都加入进 vs
    sort(vs.begin(), vs.end(), [&](auto &lhs, auto &rhs) {
        return in[lhs] < in[rhs];
    });
    st = set<int>(vs.begin(), vs.end());
    for (int i = 1; i < vs.size(); i++) {
        int gp = lca.lca(vs[i], vs[i - 1]).fi;
        st.insert(gp);
    }
    vs = vector<int>(st.begin(), st.end());
    sort(vs.begin(), vs.end(), [&](auto &lhs, auto &rhs) {
        return in[lhs] < in[rhs];
    });

    ng.edm = 0;
    for (int v : vs) ng.h[v] = -1;
    // stk 维护当前链
    stk.clear();
    for (int v : vs) {
        // 如果新点不在子树那, 那就退
        while (!stk.empty() && !issub(stk.back(), v)) stk.pop_back();

        if (!stk.empty()) {
            int cost = b[{stk.back(), v}];
            ng.add(stk.back(), v, cost);
        }

        stk.push_back(v);
    }
}

void dfs(int u, int fno, int tar) {
    f[u][0] = siz[u] - 1;
    f[u][1] = 0;
    for (int i = ng.h[u]; ~i; i = ng.ne[i]) {
        auto [v, cost] = ng.e[i];
        if (v == fno) continue;

        f[u][0] -= siz[v];
    }

    for (int i = ng.h[u]; ~i; i = ng.ne[i]) {
        auto [v, cost] = ng.e[i];
        if (v == fno) continue;

        dfs(v, u, tar);
        if (cost == tar) {
            ans += (f[v][0] + 1) * f[u][0];
            f[u][1] += f[v][0] + 1;
        } else {
            ans += (f[v][0] + 1) * f[u][1];
            ans += (f[v][1]) * f[u][0];
            f[u][0] += f[v][0] + 1;
            f[u][1] += f[v][1];
        }
    }

    ans += f[u][1];
}

void solve() {
    lca.init(n, g);
    pdfs(1, -1);

    map<int, vector<int>> mp;
    for (int u = 1; u <= n; u++) {
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            auto [v, cost] = g.e[i];

            mp[cost].push_back(u);
            mp[cost].push_back(v);
        }
    }

    ans = 0;
    for (auto &[cost, vs] : mp) {
        vs.push_back(1);
        sort(vs.begin(), vs.end());
        vs.resize(unique(vs.begin(), vs.end()) - vs.begin());

        build(vs);
        dfs(1, -1, cost);
    }

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
        cin >> n;
        g.init(n, n - 1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            b[{u, v}] = cost, b[{v, u}] = cost;
            g.add(u, v, cost), g.add(v, u, cost);
        }
        solve();
    }

    return 0;
}