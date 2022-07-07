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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;

int n;
Graph<N, N> g;
int du[N];
int dist[N], vis[N];
int mi1[N], mi2[N];

int get(int u) {
    return mi1[u] + mi2[u];
}

void upd(int u, int x) {
    if (x < mi1[u]) mi2[u] = mi1[u], mi1[u] = x;
    else if (x < mi2[u]) mi2[u] = x;
}

void solve() {
    fill(mi1, mi1 + n + 1, 1e9);
    fill(mi2, mi2 + n + 1, 1e9);

    fill(dist, dist + n + 1, 1e9);
    priority_queue<pii> que;
    for (int i = 1; i <= n; i++) {
        if (du[i] <= 1) {
            dist[i] = 0;
            que.push({0, i});
        }
    }
    while (!que.empty()) {
        auto [d, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            auto [v, cost] = g.e[i];

            upd(v, dist[u] + cost);
            if (dist[v] > get(v)) {
                dist[v] = get(v);
                que.push({-dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << (dist[i] == 1e9 ? -1 : dist[i]) << " \n"[i == n];
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
        g.init(n, -1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            g.add(u, v, cost), g.add(v, u, cost);
            du[u]++, du[v]++;
        }
        solve();
    }

    return 0;
}