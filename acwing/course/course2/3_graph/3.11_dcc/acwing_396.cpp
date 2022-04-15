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

const int N = 510;
const int M = 1010;

int n, m, Ca;
vector<pii> es;
int g[M * 4], ne[M * 4], h1[N], h2[N], edm;

void add(int h[], int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

// region v-dcc
int dfn[N], low[N], ti, rt;
vector<int> stk;
int cut[N], dcc;
vector<int> cc[N];

void tarjan(int u, int pe) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u);

    if (u == rt && h1[u] == -1) {
        dcc++;
        cc[dcc].push_back(u);
        return;
    }

    int cnt = 0;
    for (int i = h1[u]; ~i; i = ne[i]) {
        int v = g[i];
        if ((i ^ 1) == pe) continue;

        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                if (++cnt >= 2 || u != rt) cut[u] = 1;

                dcc++;
                int t;
                do {
                    t = stk.back(); stk.pop_back();
                    cc[dcc].push_back(t);
                } while (t != v);
                cc[dcc].push_back(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
// endregion

void init() {
    fill(h1, h1 + n + 1, -1), edm = 0;
    for (auto [u, v] : es) {
        add(h1, u, v), add(h1, v, u);
    }
}

void solve() {
    init();

    fill(dfn, dfn + n + 1, 0), ti = 0;
    stk.clear();
    fill(cut, cut + n + 1, 0), dcc = 0;
    for (int i = 1; i <= n; i++) cc[i].clear();

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            rt = i;
            tarjan(rt, -1);
        }
    }

    ull ans1 = 0, ans2 = 1;
    for (int k = 1; k <= dcc; k++) {
        int c = 0;
        for (int x : cc[k]) {
            c += cut[x];
        }

        int sz = cc[k].size();
        if (c == 0) {
            if (sz == 1) ans1 += 1;
            else ans1 += 2, ans2 *= sz * (sz - 1) / 2;
        } else if (c == 1) {
            ans1 += 1, ans2 *= sz - 1;
        }
    }

    cout << "Case " << ++Ca << ": " << ans1 << " " << ans2 << "\n";
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
    while (cin >> m, m) {
        n = 0;
        es.clear();
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            es.push_back({u, v});
            n = max({n, u, v});
        }
        solve();
    }

    return 0;
}