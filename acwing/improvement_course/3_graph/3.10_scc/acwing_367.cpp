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

const int N = 110;

int n;
int g[N * N], ne[N * N], h1[N], h2[N], edm;

int dfn[N], low[N], ti;
vector<int> stk;
int ins[N];
int co[N], sz[N], scc;

void add(int h[], int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u), ins[u] = 1;

    for (int i = h1[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        ++scc;
        int t;
        do {
            t = stk.back(); stk.pop_back(); ins[t] = 0;
            co[t] = scc;
            sz[scc]++;
        } while (t != u);
    }
}

void solve() {
    fill(dfn, dfn + n + 1, 0);
    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        if (!dfn[u]) {
            cnt++;
            tarjan(u);
        }
    }

    vector<int> din(scc + 1, 0), dout(scc + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int i = h1[u]; ~i; i = ne[i]) {
            int v = g[i];
            int su = co[u], sv = co[v];
            if (su == sv) continue;

            din[sv]++, dout[su]++;
        }
    }

    int c1 = 0, c2 = 0;
    for (int u = 1; u <= scc; u++) {
        c1 += din[u] == 0;
        c2 += dout[u] == 0;
    }
    cout << c1 << "\n";
    if (scc == 1) cout << 0 << "\n";
    else cout << max(c1, c2) << "\n";
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
        cin >> n;
        fill(h1, h1 + n + 1, -1), edm = 0;

        for (int u = 1; u <= n; u++) {
            int v;
            while (cin >> v, v) add(h1, u, v);
        }

        solve();
    }

    return 0;
}