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

const int N = 22;

int n, m;
int g[N][N];

void solve() {
    ll ans = 0;

    int lim = 1 << n;
    ll f[lim][n];
    memset(f, 0, sizeof f);
    for (int i = 0; i < n; i++) f[1 << i][i] = 1;
    for (int mask = 1; mask < lim; mask++) {
        int s = __lg(mask & -mask);

        for (int u = 0; u < n; u++) {
            if (mask >> u & 1) {
                if (g[u][s]) ans += f[mask][u];

                for (int v = s + 1; v < n; v++) {
                    if (!g[u][v]) continue;
                    if (mask >> v & 1) continue;

                    int ns = mask | (1 << v);
                    f[ns][v] += f[mask][u];
                }
            }
        }
    }

    ans = (ans - m) / 2;
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
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g[u][v] = g[v][u] = 1;
        }
        solve();
    }

    return 0;
}