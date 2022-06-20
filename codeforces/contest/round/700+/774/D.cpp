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

const int N = 2e5 + 10;

int n;
int g[N * 2], ne[N * 2], h[N], edm;
int sz[N];

pii f[N][2];
int ans[N];

pii& get_max(pii &a, pii &b) {
    auto [tx1, ty1] = a;
    auto [tx2, ty2] = b;
    if (tx1 > tx2) return a;
    else if (tx1 == tx2 && ty1 < ty2) return a;
    else return b;
}

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno) {
    f[u][0] = {0, 1};
    f[u][1] = {1, sz[u]};
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;

        dfs(v, u);

        f[u][1].fi += f[v][0].fi, f[u][1].se += f[v][0].se;
        pii &mx = get_max(f[v][0], f[v][1]);
        f[u][0].fi += mx.fi, f[u][0].se += mx.se;
    }
}

void dfs2(int u, int fno, int fc) {
    if (fc) {
        ans[u] = 0;
    } else {
        pii &mx = get_max(f[u][0], f[u][1]);
        ans[u] = mx == f[u][1];
    }

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;

        dfs2(v, u, ans[u]);
    }
}

void solve() {
    if (n == 2) {
        cout << "2 2\n"
                "1 1" << "\n";
        return;
    }

    dfs(1, 0);

    pii &mx = get_max(f[1][0], f[1][1]);
    ans[1] = mx == f[1][1];
    for (int i = h[1]; ~i; i = ne[i]) {
        int v = g[i];
        dfs2(v, 1, ans[1]);
    }

    cout << mx.fi << " " << mx.se << "\n";
    for (int i = 1; i <= n; i++) cout << (ans[i] ? sz[i] : 1) << " ";
    cout << "\n";
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
            sz[u]++, sz[v]++;
        }

        solve();
    }

    return 0;
}