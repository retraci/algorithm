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
const int N = 1e5 + 10;

int n;
int a[N], b[N];
Graph<N, N> g;
ll f[N], h[N];

void dfs(int u, int fno) {
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);
    }

    ll sf = 0;
    int mx = 0;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        mx = max(mx, a[v]);
        sf += f[v];
    }

    pll mx1 = {-1e18, 0}, mx2 = {-1e18, 0};
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;
        if (b[v] != 3) continue;

        pll mx3 = {a[v], v};
        if (mx3 > mx2) mx2 = mx3;
        if (mx2 > mx1) swap(mx1, mx2);
    }

    f[u] = sf + mx;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        ll t = sf + h[v] - f[v] + (v == mx1.se ? mx2.fi : mx1.fi);
        f[u] = max(f[u], t);
    }

    h[u] = sf + a[u];
}

void solve() {
    dfs(1, -1);

    ll ans = f[1] + a[1];
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
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        g.init(n, -1);
        for (int i = 2; i <= n; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v), g.add(v, u);
        }

        solve();
    }

    return 0;
}