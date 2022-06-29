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
const int N = (1 << 17) + 10;

int n, p;
Graph<N, N> g;

void solve() {
    static queue<pii> que;

    vector<int> av(n + 1), ae(n);
    vector<int> vis(n + 1);
    av[1] = 1 << p;
    vis[1] = 1;
    que.push({1, 1 << p});
    int cnt = 0;
    while (!que.empty()) {
        auto [u, w] = que.front(); que.pop();

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (vis[v]) continue;

            vis[v] = 1;
            cnt++;
            if (w == 0) {
                ae[i / 2] = cnt;
                av[v] = (1 << p) + cnt;
            } else {
                ae[i / 2] = (1 << p) + cnt;
                av[v] = cnt;
            }

            que.push({v, w ^ n});
        }
    }

    cout << 1 << "\n";
    for (int i = 1; i <= n; i++) cout << av[i] << " \n"[i == n];
    for (int i = 0; i < n - 1; i++) cout << ae[i] << " \n"[i == n - 2];
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
        cin >> p;
        n = 1 << p;
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