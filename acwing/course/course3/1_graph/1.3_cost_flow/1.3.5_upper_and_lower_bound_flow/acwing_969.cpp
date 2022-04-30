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

const int N = 1010;
const int M = 10010;

int n, m, S, T;
int a[N];
ai3 b[M];
Flow<N, 3 * N + M> g;

void init() {
    S = n + 1 + 1, T = n + 1 + 2;
    g.init(n + 3);

    vector<int> dta(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        g.add(i, i + 1, 1e9, 0);
        dta[i] += a[i], dta[i + 1] -= a[i];
    }
    for (int i = 1; i <= n + 1; i++) {
        if (dta[i] > 0) g.add(i, T, dta[i], 0);
        if (dta[i] < 0) g.add(S, i, -dta[i], 0);
    }

    for (int i = 1; i <= m; i++) {
        auto [s, t, c] = b[i];

        g.add(t + 1, s, 1e9, c);
    }
}

void solve() {
    init();

    int ans = g.max_flow_cost(S, T).se;
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int s, t, c;
            cin >> s >> t >> c;
            b[i] = {s, t, c};
        }
        solve();
    }

    return 0;
}