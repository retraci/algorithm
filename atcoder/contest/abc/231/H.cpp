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
#include <cassert>
#include <random>
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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region dinic 费用流
template<int N, int M>
struct Flow {
    using flowt = ll;
    using pff = pair<flowt, flowt>;
    using af3 = array<flowt, 3>;
    const flowt INF = 1e18;

    int n;
    af3 e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int nh[N + 10], vis[N + 10];
    flowt d[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt cap, flowt cost) {
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool spfa(int S, int T, int is_max_flow = 1) {
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

        // 可行流: cost = d[T] * flow, 若最小费用, 则 d[T] < 0
        if (is_max_flow) return d[T] != INF;
        else return d[T] != INF && d[T] < 0;
    }

    pff dfs(int u, int T, flowt lit) {
        if (u == T) return {lit, lit * d[T]};
        vis[u] = 1;

        flowt flow = 0, dis = 0;
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

    pff max_flow_cost(int S, int T) {
        flowt flow = 0, dis = 0;
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

    pff feasible_flow_cost(int S, int T) {
        flowt flow = 0, dis = 0;
        while (spfa(S, T, 0)) {
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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e3 + 10;

int h, w, n;
ai3 a[N];
int S, T;
Flow<2 * N, 3 * N> flow;

void solve() {
    vector<int> rs(h + 1), cs(w + 1);
    for (int i = 1; i <= n; i++) {
        auto [x, y, c] = a[i];
        rs[x]++, cs[y]++;
    }

    int tt = h + w + 2;
    S = tt - 1, T = tt;
    flow.init(tt);
    for (int i = 1; i <= h; i++) flow.add(S, i, rs[i] - 1, 0);
    for (int i = 1; i <= w; i++) flow.add(h + i, T, cs[i] - 1, 0);
    for (int i = 1; i <= n; i++) {
        auto [x, y, c] = a[i];
        flow.add(x, h + y, 1, -c);
    }

    auto [f, c] = flow.feasible_flow_cost(S, T);
    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += a[i][2];
    ans -= -c;
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
        cin >> h >> w >> n;
        for (int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1] >> a[i][2];
        solve();
    }

    return 0;
}