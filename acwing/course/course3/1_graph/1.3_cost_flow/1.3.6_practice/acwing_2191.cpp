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
//        debug(u, v, cap, cost);
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool spfa(int S, int T) {
        fill(d + 1, d + n + 1, INF);
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
                        if (!que.empty() && d[v] <= d[que.front()]) que.push_front(v);
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

const int N = 22;

int n, m, nl;
int a[N][N];
vector<pii> lsh;
Flow<4 * N * N, 3 * N + 8 * N * N> g;

int get(int x, int y) {
    return lower_bound(lsh.begin(), lsh.end(), (pii) {x, y}) - lsh.begin();
}

int work1() {
    int S = 2 * nl + 1, T = 2 * nl + 2;
    g.init(2 * nl + 2);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int x = get(i, j) + 1;
            g.add(x, nl + x, 1, -a[i][j]);
        }
    }
    for (int j = 1; j <= m; j++) {
        int x = get(1, j) + 1;
        g.add(S, x, 1, 0);
    }
    for (int j = 1; j <= n + m - 1; j++) {
        int x = get(n, j) + 1;
        g.add(nl + x, T, 1, 0);
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int u = get(i, j) + 1, v = get(i + 1, j) + 1;
            g.add(nl + u, v, 1, 0);

            v = get(i + 1, j + 1) + 1;
            g.add(nl + u, v, 1, 0);
        }
    }

    return -g.max_flow_cost(S, T).se;
}

int work2() {
    int S = 2 * nl + 1, T = 2 * nl + 2;
    g.init(2 * nl + 2);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int x = get(i, j) + 1;
            g.add(x, nl + x, 1e9, -a[i][j]);
        }
    }
    for (int j = 1; j <= m; j++) {
        int x = get(1, j) + 1;
        g.add(S, x, 1, 0);
    }
    for (int j = 1; j <= n + m - 1; j++) {
        int x = get(n, j) + 1;
        g.add(nl + x, T, 1e9, 0);
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int u = get(i, j) + 1, v = get(i + 1, j) + 1;
            g.add(nl + u, v, 1, 0);

            v = get(i + 1, j + 1) + 1;
            g.add(nl + u, v, 1, 0);
        }
    }

    return -g.max_flow_cost(S, T).se;
}

int work3() {
    int S = 2 * nl + 1, T = 2 * nl + 2;
    g.init(2 * nl + 2);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int x = get(i, j) + 1;
            g.add(x, nl + x, 1e9, -a[i][j]);
        }
    }
    for (int j = 1; j <= m; j++) {
        int x = get(1, j) + 1;
        g.add(S, x, 1, 0);
    }
    for (int j = 1; j <= n + m - 1; j++) {
        int x = get(n, j) + 1;
        g.add(nl + x, T, 1e9, 0);
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            int u = get(i, j) + 1, v = get(i + 1, j) + 1;
            g.add(nl + u, v, 1e9, 0);

            v = get(i + 1, j + 1) + 1;
            g.add(nl + u, v, 1e9, 0);
        }
    }

    return -g.max_flow_cost(S, T).se;
}

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m + i - 1; j++) {
            lsh.push_back({i, j});
        }
    }
    nl = lsh.size();
}

void solve() {
    init();

    cout << work1() << "\n";
    cout << work2() << "\n";
    cout << work3() << "\n";
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
        cin >> m >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m + i - 1; j++) {
                cin >> a[i][j];
            }
        }
        solve();
    }

    return 0;
}