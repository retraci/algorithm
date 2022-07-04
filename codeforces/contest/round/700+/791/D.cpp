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

ll n, m, k;
int a[N];
pii es[N];
Graph<N, N> g;

bool check(int md) {
    static queue<int> que;
    static int din[N], f[N];

    for (int i = 1; i <= n; i++) din[i] = 0;
    g.init(n, -1);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        if (a[u] > md || a[v] > md) continue;

        g.add(u, v);
        din[v]++;
    }

    for (int i = 1; i <= n; i++) f[i] = -1e9;
    for (int i = 1; i <= n; i++) {
        if (a[i] > md) continue;

        if (din[i] == 0) {
            f[i] = 1;
            que.push(i);
        }
    }

    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];

            f[v] = max(f[v], f[u] + 1);
            if (--din[v] == 0) que.push(v);
        }
    }

    int mxd = *max_element(din + 1, din + n + 1);
    int mx = *max_element(f + 1, f + n + 1);
    return mxd > 0 || mx >= k;
}

void solve() {
    int left = 1, right = 1e9 + 1;
    while (left < right) {
        int md = left + right >> 1;
        if (check(md)) right = md;
        else left = md + 1;
    }

    int ans = left == 1e9 + 1 ? -1 : left;
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
        cin >> n >> m >> k;

        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;

            es[i] = {u, v};
        }
        solve();
    }

    return 0;
}