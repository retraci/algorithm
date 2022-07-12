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

int n, mod;
Graph<N, N> g;
int f[N], f2[N], ans[N];

void pdfs(int u, int fno) {
    f[u] = 1;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        pdfs(v, u);

        f[u] = 1LL * f[u] * (f[v] + 1) % mod;
    }
}

void dfs(int u, int fno) {
    static int pre[N], suf[N];

    int sz = 0;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        sz++;
        pre[sz] = suf[sz] = f[v] + 1;
    }
    pre[0] = 1;
    for (int i = 1; i <= sz; i++) pre[i] = 1LL * pre[i] * pre[i - 1] % mod;
    suf[sz + 1] = 1;
    for (int i = sz; i >= 1; i--) suf[i] = 1LL * suf[i] * suf[i + 1] % mod;

    int cur = 1;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        f2[v] = u == 1 ? 1 : f2[u] + 1;
        f2[v] = 1LL * f2[v] * pre[cur - 1] % mod * suf[cur + 1] % mod;
        cur++;
    }

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        ans[v] = 1LL * f[v] * (f2[v] + 1) % mod;
        dfs(v, u);
    }
}

void solve() {
    pdfs(1, -1);

    ans[1] = f[1];
    dfs(1, -1);
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
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
        cin >> n >> mod;
        g.init(n, -1);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            g.add(p, i);
        }
        solve();
    }

    return 0;
}