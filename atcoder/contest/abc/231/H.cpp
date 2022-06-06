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

// region primal-dual 费用流
template<int N, int M>
struct Flow {
    using flowt = ll;
    using pff = pair<flowt, flowt>;
    using af3 = array<flowt, 3>;
    const flowt INF = 1e18;

    int n;
    af3 e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int pre[N + 10];
    flowt d[N + 10], r[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt cap, flowt cost) {
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool dij(int S, int T) {
        static int vis[N + 10];
        static priority_queue<pff> que;
        fill(d, d + n + 1, INF);
        fill(vis, vis + n + 1, 0);

        d[S] = 0;
        que.push({0, S});
        while (!que.empty()) {
            auto [_, u] = que.top(); que.pop();
            if (vis[u]) continue;
            vis[u] = 1;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap, cost] = e[i];
                if (cap == 0) continue;

                flowt nc = cost + r[u] - r[v];
                if (d[v] > d[u] + nc) {
                    d[v] = d[u] + nc;
                    pre[v] = i;
                    que.push({-d[v], v});
                }
            }
        }

        return d[T] != INF;
    }

    void spfa(int S, int T) {
        static int inq[N + 10] = {0};
        static deque<int> que;
        fill(r + 1, r + n + 1, INF);

        r[S] = 0, inq[S] = 1;
        que.push_back(S);
        while (!que.empty()) {
            auto u = que.front(); que.pop_front();
            inq[u] = 0;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap, cost] = e[i];
                if (cap == 0) continue;

                if (r[v] > r[u] + cost) {
                    r[v] = r[u] + cost;

                    if (!inq[v]) {
                        inq[v] = 1;
                        if (!que.empty() && r[v] < r[que.front()]) que.push_front(v);
                        else que.push_back(v);
                    }
                }
            }
        }
    }

    pff mcmf(int S, int T) {
        spfa(S, T);
        flowt flow = 0, fco = 0;
        while (dij(S, T)) {
            for (int i = 1; i <= n; i++) r[i] += d[i];

            flowt minf = INF;
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) minf = min(minf, e[pre[i]][1]);
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) {
                e[pre[i]][1] -= minf, e[pre[i] ^ 1][1] += minf;
            }

            flow += minf, fco += minf * r[T];
        }

        return {flow, fco};
    }

    pff mcff(int S, int T) {
        spfa(S, T);
        flowt flow = 0, fco = 0;
        while (dij(S, T)) {
            for (int i = 1; i <= n; i++) r[i] += d[i];
            if (r[T] >= 0) break;

            flowt minf = INF;
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) minf = min(minf, e[pre[i]][1]);
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) {
                e[pre[i]][1] -= minf, e[pre[i] ^ 1][1] += minf;
            }

            flow += minf, fco += minf * r[T];
        }

        return {flow, fco};
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

    auto [f, c] = flow.mcff(S, T);
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