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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n;
Graph<N, N> g;
int vis[N], ins[N];
int f[N][2];
int ans;

void dfs(int u, int eid, int sp) {
    f[u][0] = 0, f[u][1] = -1e9;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (i == eid) continue;

        dfs(v, eid, sp);
        f[u][0] += max(f[v][0], f[v][1]);
    }

    if (u == sp) {
        f[u][1] = f[u][0] + 1, f[u][0] = -1e9;
    } else {
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (i == eid) continue;

            int mx = max(f[v][0], f[v][1]);
            f[u][1] = max(f[u][1], f[u][0] - mx + f[v][0] + 1);
        }
    }
}

void pdfs(int u) {
    vis[u] = ins[u] = 1;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];

        if (!vis[v]) {
            pdfs(v);
        } else if (ins[v]) {
            dfs(v, i, -1);
            int mx = max(f[v][0], f[v][1]);
            dfs(v, i, u);
            mx = max(mx, f[v][0]);
            ans += mx;
        }
    }

    ins[u] = 0;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        pdfs(i);
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
        g.init(n, n);

        for (int i = 1; i <= n; i++) {
            int v;
            cin >> v;
            g.add(v, i);
        }
        solve();
    }

    return 0;
}