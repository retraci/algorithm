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
#include <cassert>
#include <random>
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
using ai4 = array<int, 4>;

// region 无权的lca
template<int N, class G>
struct Lca {
    int n, mxb;
    int dep[N + 10], fa[__lg(N) + 1][N + 10];

    Lca() {}

    void init(int rt, const G &g) {
        n = g.n, mxb = __lg(n);
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1, fa[0][rt] = 0;
        while (!que.empty()) {
            auto u = que.front(); que.pop();

            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];

                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    fa[0][v] = u;
                    que.push(v);
                }
            }
        }

        for (int k = 1; k <= mxb; k++) {
            for (int v = 1; v <= n; v++) {
                fa[k][v] = fa[k - 1][fa[k - 1][v]];
            }
        }
    }

    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) {
                x = fa[k][x];
            }
        }
        if (x == y) return x;

        for (int k = mxb; k >= 0; k--) {
            if (fa[k][x] != fa[k][y]) {
                x = fa[k][x], y = fa[k][y];
            }
        }
        return fa[0][x];
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
const int N = 40010;
const int M = 1e5 + 10;

using G = Graph<N, M>;

int n, m;
int a[N];
pii b[M];
ai4 qs[M];

G g;
Lca<N, G> lca;
int eula[2 * N], ein[N], eout[N], cnt;
int bl;
int vis[N], c[N], cur;
vector<int> lsh;
int nl;

void dfs(int u, int fno) {
    eula[++cnt] = u, ein[u] = cnt;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);
    }

    eula[++cnt] = u, eout[u] = cnt;
}

int get_lsh(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) a[i] = get_lsh(a[i]) + 1;

    lca.init(1, g);
    cnt = 0;
    dfs(1, 0);

    for (int i = 1; i <= m; i++) {
        auto [L, R] = b[i];
        if (ein[L] > ein[R]) swap(L, R);
        int p = lca.lca(L, R);
        if (p != L) qs[i] = {i, eout[L], ein[R], p};
        else qs[i] = {i, ein[L], ein[R], 0};
    }
}

void add(int p) {
    vis[p] ^= 1;
    if (vis[p]) {
        if (++c[a[p]] == 1) cur++;
    } else {
        if (--c[a[p]] == 0) cur--;
    }
}

int get(int i) {
    return (i - 1) / bl + 1;
}

void solve() {
    init();

    bl = sqrt(2 * n);
    sort(qs + 1, qs + m + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[2] < b[2] : a[2] > b[2];
    });

    vector<int> ans(m + 1);
    fill(vis, vis + n + 1, 0), cur = 0;
    int cl = 1, cr = 0;
    for (int i = 1; i <= m; i++) {
        auto [qid, L, R, p] = qs[i];

        while (cl < L) add(eula[cl++]);
        while (cl > L) add(eula[--cl]);
        while (cr > R) add(eula[cr--]);
        while (cr < R) add(eula[++cr]);

        if (p) add(p);
        ans[qid] = cur;
        if (p) add(p);
    }

    for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
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
        g.init(n, m);

        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v), g.add(v, u);
        }
        for (int i = 1; i <= m; i++) cin >> b[i].fi >> b[i].se;

        solve();
    }

    return 0;
}