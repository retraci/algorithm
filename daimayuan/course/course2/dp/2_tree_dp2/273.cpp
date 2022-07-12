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
const int N = 2010;

int n, m;
Graph<N, N> g;
ai3 a[N];
vector<int> b[N];
int dep[N];
ll f[N][N];

void pdfs(int u, int fno) {
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dep[v] = dep[u] + 1;
        pdfs(v, u);
    }
}

void dfs(int u, int fno) {
    static ll suf1[N], suf2[N];

    for (int i = 1; i <= dep[u]; i++) f[u][i] = 1e18;
    for (int i : b[u]) {
        auto [tu, tv, cost] = a[i];

        f[u][dep[tv]] = min(f[u][dep[tv]], 1LL * cost);
    }

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);

        suf1[dep[v] + 1] = suf2[dep[v] + 1] = 1e18;
        for (int j = dep[v]; j >= 1; j--) suf1[j] = min(suf1[j + 1], f[u][j]), suf2[j] = min(suf2[j + 1], f[v][j]);
        for (int j = 1; j <= dep[v]; j++) f[u][j] = min({(ll) 1e18, f[u][j] + suf2[j], f[v][j] + suf1[j]});
    }
}

void solve() {
    dep[1] = 1;
    pdfs(1, -1);

    for (int i = 1; i <= m; i++) {
        auto &[u, v, cost] = a[i];

        if (dep[u] < dep[v]) swap(u, v);
        b[u].push_back(i);
    }

    dfs(1, -1);

    cout << (f[1][1] == 1e18 ? -1 : f[1][1]) << "\n";
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
        g.init(n, -1);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            g.add(p, i);
        }
        for (int i = 1; i <= m; i++) cin >> a[i][0] >> a[i][1] >> a[i][2];
        solve();
    }

    return 0;
}