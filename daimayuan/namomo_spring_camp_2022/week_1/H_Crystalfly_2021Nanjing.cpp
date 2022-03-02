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

int n;
int a[N], b[N];
int g[N * 2], ne[N * 2], h[N], edm;

ll f[N], sum[N];

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno) {
    int mx = 0, mx1 = 0, mx2 = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;
        dfs(v, u);

        sum[u] += f[v];
        mx = max(mx, a[v]);
        if (b[v] == 3) {
            if (a[v] > mx1) {
                mx2 = mx1;
                mx1 = a[v];
            } else if (a[v] > mx2) {
                mx2 = a[v];
            }
        }
    }

    f[u] = sum[u] + mx;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;

        ll tmp = sum[u] - f[v] + a[v] + sum[v];
        if (b[v] == 3 && a[v] == mx1) tmp += mx2;
        else tmp += mx1;
        f[u] = max(f[u], tmp);
    }
}

void solve() {
    fill(sum, sum + n + 1, 0);
    dfs(1, -1);

    cout << f[1] + a[1] << "\n";
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
    cin >> T;
    while (T--) {
        cin >> n;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }

        solve();
    }

    return 0;
}