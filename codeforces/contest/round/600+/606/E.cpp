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
const int N = 2e5 + 10;
const int M = 5e5 + 10;

int n, m, a, b;
Graph<N, M> g;
int vis[N];

void dfs(int u, int c, int ban) {
    if (u == ban) return;
    if (vis[u] & c) return;
    vis[u] += c;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];

        dfs(v, c, ban);
    }
}

void solve() {
    fill(vis, vis + n + 1, 0);
    dfs(a, 1, b);
    dfs(b, 2, a);

    int c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 3 || i == a || i == b) continue;
        c1 += vis[i] >> 0 & 1;
        c2 += vis[i] >> 1 & 1;
    }

    ll ans = 1LL * c1 * c2;
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
        cin >> n >> m >> a >> b;
        g.init(n, m);

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v), g.add(v, u);
        }
        solve();
    }

    return 0;
}