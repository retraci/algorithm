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

const int N = 5010;
const int M = 10010;

int n, m;
int g[M * 4], ne[M * 4], h1[N], h2[N], edm;

int dfn[N], low[N], ti;
vector<int> stk;
int co[N], sz[N], dcc;
int br[M * 2];

void add(int h[], int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void tarjan(int u, int pe) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u);

    for (int i = h1[u]; ~i; i = ne[i]) {
        int v = g[i];
        if ((i ^ 1) == pe) continue;

        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);

            if (low[v] > dfn[u]) br[i] = br[i ^ 1] = 1;
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        dcc++;
        int t;
        do {
            t = stk.back(); stk.pop_back();
            co[t] = dcc;
            sz[dcc]++;
        } while (t != u);
    }
}

void solve() {
    fill(dfn, dfn + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i, -1);
    }

    vector<int> du(dcc + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int i = h1[u]; ~i; i = ne[i]) {
            if (br[i]) {
                int v = g[i];
                int cu = co[u], cv = co[v];
                du[cv]++;
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i <= dcc; i++) {
        cnt += du[i] == 1;
    }
    cout << (cnt + 1) / 2 << "\n";
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

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(h1, u, v), add(h1, v, u);
        }

        solve();
    }

    return 0;
}