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
const int N = 50010;
const int M = 110;
const int B = 100;
const int INF = 1e9;

int n, q;
int a[N];
Graph<N, N> g;
int f[N][M];
int sz[N];

void dfs(int u, int fno) {
    static int tmp[M];

    sz[u] = 0;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);

        for (int j = 0; j <= sz[u] + sz[v] && j <= B; j++) tmp[j] = -INF;
        for (int j = 0; j <= min(B, sz[u]) && j <= B; j++) {
            for (int k = 0; k <= min(B, sz[v]) && j + k <= B; k++) {
                tmp[j + k] = max(tmp[j + k], f[u][j] + f[v][k]);
            }
        }

        for (int j = 0; j <= sz[u] + sz[v] && j <= B; j++) f[u][j] = tmp[j];
        sz[u] += sz[v];
    }

    sz[u]++;
    for (int j = min(B, sz[u]); j >= 1; j--) f[u][j] = f[u][j - 1] + a[u];
    f[u][0] = 0;
}

void solve() {
    dfs(1, -1);

    while (q--) {
        int u, m;
        cin >> u >> m;

        cout << f[u][m] << "\n";
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
        cin >> n >> q;
        g.init(n, -1);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            g.add(p, i);
        }
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}