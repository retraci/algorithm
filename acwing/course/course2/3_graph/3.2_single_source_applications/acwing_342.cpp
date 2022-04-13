#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 25010;
const int M = 150010;

int n, R, P, s;
ti3 va[M], vb[M];
pii g[M];
int ne[M], h[N], edm;

int co[N], scc;
vector<int> gc[N];
int du[N];

queue<int> que;
int dist[N];
int vis[N];

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int c) {
    co[u] = c, gc[c].push_back(u);

    for (int i = h[u]; ~i; i = ne[i]) {
        auto [cost, v] = g[i];
        if (co[v]) continue;
        dfs(v, c);
    }
}

void init() {
    for (int i = 1; i <= R; i++) {
        auto [u, v, cost] = va[i];
        add(u, v, cost), add(v, u, cost);
    }

    for (int i = 1; i <= n; i++) {
        if (co[i]) continue;
        dfs(i, ++scc);
    }

    for (int i = 1; i <= P; i++) {
        auto [u, v, cost] = vb[i];
        add(u, v, cost);
        du[co[v]]++;
    }
}

void dij(int c) {
    priority_queue<pii> pq;
    for (int x : gc[c]) pq.push({-dist[x], x});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v] > dist[u] + cost) {
                if (dist[u] < 1e9) dist[v] = dist[u] + cost;
                if (co[v] == co[u]) pq.push({-dist[v], v});
            }

            if (co[v] != co[u] && --du[co[v]] == 0) que.push(co[v]);
        }
    }
}

void topo() {
    fill(&dist[1], &dist[n] + 1, 1e9), memset(vis, 0, sizeof vis);
    dist[s] = 0;

    for (int i = 1; i <= scc; i++) {
        if (du[i] == 0) que.push(i);
    }
    while (!que.empty()) {
        auto u = que.front(); que.pop();
        dij(u);

        for (int i = 1; i <= n; i++) {
            cout << dist[i] << " ";
        }
        cout << "\n";
    }
}

void solve() {
    init();

    topo();

    for (int i = 1; i <= n; i++) {
        if (dist[i] == 1e9) cout << "NO PATH" << "\n";
        else cout << dist[i] << "\n";
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> R >> P >> s;
        memset(h, -1, sizeof h);

        for (int i = 1; i <= R; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            va[i] = {u, v, cost};
        }
        for (int i = 1; i <= P; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            vb[i] = {u, v, cost};
        }
        solve();
    }

    return 0;
}