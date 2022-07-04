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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 100010;

int n;
int a[N];
Graph<N, N> g;
int sz[N], son[N];
ll ans[N], cnt[N], mx, s;

void pdfs(int u, int fno) {
    sz[u] = 1;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        pdfs(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

void upd(int u, int fno, int sgn, int hson) {
    cnt[a[u]] += sgn;
    if (mx < cnt[a[u]]) {
        mx = cnt[a[u]], s = a[u];
    } else if (mx == cnt[a[u]]) {
        s += a[u];
    }

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;
        if (v == hson) continue;

        upd(v, u, sgn, hson);
    }
}

void dfs(int u, int fno, int op) {
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;
        if (v == son[u]) continue;

        dfs(v, u, 0);
    }
    if (son[u]) dfs(son[u], u, 1);

    upd(u, fno, 1, son[u]);
    ans[u] = s;

    if (!op) upd(u, fno, -1, 0), s = 0, mx = 0;
}

void solve() {
    pdfs(1, -1);

    dfs(1, -1, 1);

    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
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
        for (int i = 1; i <= n; i++) cin >> a[i];

        g.init(n, n - 1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v), g.add(v, u);
        }
        solve();
    }

    return 0;
}