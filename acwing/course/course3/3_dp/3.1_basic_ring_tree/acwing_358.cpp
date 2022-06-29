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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n;
Graph<N, N> g;
int vis[N], ins[N];
pii pre[N];
int cnt;
vector<pii> cs[N];
ll cur;

void pdfs(int u, int pe) {
    vis[u] = ins[u] = 1;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        if ((i ^ 1) == pe) continue;
        auto [v, cost] = g.e[i];

        if (!vis[v]) {
            pre[v] = {u, cost};
            pdfs(v, i);
        } else if (ins[v]) {
            cs[++cnt].push_back({u, cost});
            int t = u;
            while (t != v) {
                auto [pv, pc] = pre[t];
                cs[cnt].push_back(pre[t]);
                t = pv;
            }
        }
    }

    ins[u] = 0;
}

ll dfs(int u, int fno) {
    ll d1 = 0, d2 = 0;
    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        auto [v, cost] = g.e[i];
        if (vis[v] || v == fno) continue;

        ll t = dfs(v, u) + cost;
        if (t > d1) d2 = d1, d1 = t;
        else if (t > d2) d2 = t;
    }

    cur = max(cur, d1 + d2);
    return d1;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        pdfs(i, -1);
    }

    fill(vis + 1, vis + n + 1, 0);
    for (int k = 1; k <= cnt; k++) {
        for (auto [u, cost] : cs[k]) vis[u] = 1;
    }

    ll ans = 0;
    for (int k = 1; k <= cnt; k++) {
        cur = 0;

        static ll d[2 * N], s[2 * N];
        int m = 0;
        for (auto [u, cost] : cs[k]) {
            m++;
            d[m] = dfs(u, -1);
            s[m] = cost;
        }

        for (int i = 1; i <= m; i++) s[i] += s[i - 1];
        for (int i = 1; i <= m; i++) {
            d[i + m] = d[i];
            s[i + m] = s[i] + s[m];
        }

        static int que[N * 2], hh, tt;
        hh = 0, tt = -1;
        for (int i = 1; i <= 2 * m; i++) {
            while (hh <= tt && i - que[hh] >= m) hh++;
            if (hh <= tt) cur = max(cur, d[i] + s[i] + d[que[hh]] - s[que[hh]]);
            while (hh <= tt && d[que[tt]] - s[que[tt]] <= d[i] - s[i]) tt--;
            que[++tt] = i;
        }

        ans += cur;
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
            int v, cost;
            cin >> v >> cost;
            g.add(i, v, cost), g.add(v, i, cost);
        }
        solve();
    }

    return 0;
}