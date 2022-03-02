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

const int N = 1e5 + 10;
const int M = 3e5 + 10;

int n, m, mod;
pii g[2 * M];
int ne[2 * M], h1[N], h2[N], edm;

int flag;

// region scc 缩点
int dfn[N], low[N], ti;
vector<int> stk;
int ins[N];
int co[N], sz[N], scc;

void tarjan(int u) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u), ins[u] = 1;

    for (int i = h1[u]; ~i; i = ne[i]) {
        auto [cost, v] = g[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        scc++;
        int t;
        do {
            t = stk.back(); stk.pop_back(); ins[t] = 0;
            co[t] = scc;
            sz[scc]++;
        } while (t != u);
    }
}
// endregion

void add(int h[], int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void init() {
    for (int i = 1; i <= n; i++) add(h1, 0, i, 1);

    fill(dfn, dfn + n + 1, 0);
    for (int i = 0; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    flag = 0;
    fill(h2, h2 + scc + 1, -1);
    for (int u = 0; u <= n; u++) {
        for (int i = h1[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];
            int su = co[u], sv = co[v];

            if (su == sv) {
                if (cost > 0) {
                    flag = 1;
                    return;
                }
            } else {
                add(h2, su, sv, cost);
            }
        }
    }
}

void solve() {
    init();

    if (flag) {
        cout << -1 << "\n";
        return;
    }

    vector<ll> f(scc + 1, 0);
    for (int u = scc; u >= 1; u--) {
        for (int i = h2[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];
            f[v] = max(f[v], f[u] + cost);
        }
    }

    ll ans = 0;
    for (int i = 1; i <= scc; i++) ans += sz[i] * f[i];
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> m;
        fill(h1, h1 + n + 1, -1), edm = 0;

        while (m--) {
            int x, u, v;
            cin >> x >> u >> v;
            if (x == 1) add(h1, u, v, 0), add(h1, v, u, 0);
            else if (x == 2) add(h1, u, v, 1);
            else if (x == 3) add(h1, v, u, 0);
            else if (x == 4) add(h1, v, u, 1);
            else add(h1, u, v, 0);
        }
        solve();
    }

    return 0;
}