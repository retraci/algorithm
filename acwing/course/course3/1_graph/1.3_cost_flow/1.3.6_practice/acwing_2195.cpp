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
#include <cmath>

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
using ull = unsigned long long;
using pii = pair<int, int>;
using ai3 = array<int, 3>;

// region dinic 整数费用流
template<int N, int M>
struct Flow {
    using ai3 = array<int, 3>;
    const int INF = 1e9;

    int n;
    ai3 e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int d[N + 10], nh[N + 10], vis[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, int cap, int cost) {
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool spfa(int S, int T) {
        fill(d, d + n + 1, INF);
        vector<int> inq(n + 1, 0);

        deque<int> que;
        d[S] = 0, inq[S] = 1;
        que.push_back(S);
        while (!que.empty()) {
            auto u = que.front(); que.pop_front();
            inq[u] = 0;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap, cost] = e[i];
                if (cap == 0) continue;

                if (d[v] > d[u] + cost) {
                    d[v] = d[u] + cost;

                    if (!inq[v]) {
                        inq[v] = 1;
                        if (!que.empty() && d[v] < d[que.front()]) que.push_front(v);
                        else que.push_back(v);
                    }
                }
            }
        }

        return d[T] != INF;
    }

    pii dfs(int u, int T, int lit) {
        if (u == T) return {lit, lit * d[T]};
        vis[u] = 1;

        int flow = 0, dis = 0;
        for (int &i = nh[u]; ~i; i = ne[i]) {
            auto &[v, cap, cost] = e[i];
            if (d[v] != d[u] + cost || cap == 0 || vis[v]) continue;

            auto [t1, t2] = dfs(v, T, min(cap, lit - flow));
            if (t1 == 0) d[v] = INF;
            flow += t1, dis += t2, cap -= t1, e[i ^ 1][1] += t1;

            if (lit - flow == 0) break;
        }

        vis[u] = 0;
        return {flow, dis};
    }

    pii max_flow_cost(int S, int T) {
        int flow = 0, dis = 0;
        while (spfa(S, T)) {
            for (int i = 1; i <= n; i++) nh[i] = h[i];
            while (1) {
                auto [t1, t2] = dfs(S, T, INF);
                if (t1 == 0) break;

                flow += t1, dis += t2;
            }
        }

        return {flow, dis};
    }
};
// endregion

const int N = 17;

int cs, ct, n, m, S, T;
int a[N][N], b[N][N];
ai3 sp[N], tp[N];
Flow<N * N, N * N * 4 + 10> g;

int get(int x, int y) {
    return x * (m + 1) + y + 1;
}

void init() {
    S = (n + 1) * (m + 1) + 1, T = (n + 1) * (m + 1) + 2;
    g.init((n + 1) * (m + 1) + 2);

    for (int i = 1; i <= cs; i++) {
        auto [x, y, cnt] = sp[i];
        int id = get(x, y);

        g.add(S, id, cnt, 0);
    }
    for (int i = 1; i <= ct; i++) {
        auto [x, y, cnt] = tp[i];
        int id = get(x, y);

        g.add(id, T, cnt, 0);
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            int u = get(i, j), v = get(i, j + 1);

            g.add(u, v, 1, -a[i][j]);
            g.add(u, v, 1e9, 0);
        }
    }
    for (int j = 0; j <= m; j++) {
        for (int i = 0; i < n; i++) {
            int u = get(i, j), v = get(i + 1, j);

            g.add(u, v, 1, -b[i][j]);
            g.add(u, v, 1e9, 0);
        }
    }
}

void solve() {
    init();

    int ans = -g.max_flow_cost(S, T).se;
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
        cin >> cs >> ct >> n >> m;

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        for (int j = 0; j <= m; j++) {
            for (int i = 0; i < n; i++) {
                cin >> b[i][j];
            }
        }
        for (int i = 1; i <= cs; i++) {
            int x, y, cnt;
            cin >> cnt >> x >> y;
            sp[i] = {x, y, cnt};
        }
        for (int i = 1; i <= ct; i++) {
            int x, y, cnt;
            cin >> cnt >> x >> y;
            tp[i] = {x, y, cnt};
        }

        solve();
    }

    return 0;
}