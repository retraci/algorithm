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
const int N = 1010;
const int INF = 1e9;

int n, m;
int a[N], w[N];
Graph<N, N> g;
int in[N], out[N], id[N], ti;

void dfs(int u, int fno) {
    id[++ti] = u, in[u] = ti;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);
    }

    out[u] = ti;
}

void solve() {
    dfs(1, -1);

    int f[n + 2][m + 1];
    fill(&f[0][0], &f[n + 1][m] + 1, -INF);
    f[n + 1][0] = 0;
    for (int i = n; i >= 1; i--) {
        int u = id[i];
        for (int j = 0; j <= m; j++) {
            f[i][j] = f[out[u] + 1][j];
            if (j >= w[u]) f[i][j] = max(f[i][j], f[i + 1][j - w[u]] + a[u]);
        }
    }

    for (int j = 0; j <= m; j++) {
        cout << (f[1][j] < 0 ? 0 : f[1][j]) << "\n";
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
        cin >> n >> m;
        g.init(n, -1);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            g.add(p, i);
        }
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> w[i];
        solve();
    }

    return 0;
}