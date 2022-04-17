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

const int N = 10010;
const int M = 15010;

int n, m;
int g[M * 4], ne[M * 4], h1[N], h2[N], edm;
int mx;

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

    if (u == rt) mx = max(mx, cnt);
    else mx = max(mx, cnt + 1);
}
// endregion

void solve() {
    mx = 0;
    int c = 0;

    fill(dfn, dfn + n + 1, 0), ti = 0;
    stk.clear();
    for (int i = 1; i <= n; i++) cc[i].clear();
    fill(cut, cut + n + 1, 0), dcc = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            c++;
            rt = i;
            tarjan(rt, -1);
        }
    }

    int ans = c + mx - 1;
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
    while (cin >> n >> m, n || m) {
        fill(h1, h1 + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            u++, v++;
            add(h1, u, v), add(h1, v, u);
        }

        solve();
    }

    return 0;
}