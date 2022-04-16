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

const int N = 33;

int n, m, x;
int g[N][N];

ll calc(int lim) {
    ll f[x + 1][n + 1][m + 1];
    memset(f, 0x3f, sizeof f);
    f[0][1][0] = f[0][0][1] = 0;
    for (int k = 0; k <= x; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (g[i][j] >= lim) {
                    int pk = k - 1;
                    if (pk >= 0) {
                        ll tmp = min(f[pk][i - 1][j], f[pk][i][j - 1]) + g[i][j];
                        f[k][i][j] = min(f[k][i][j], tmp);
                    }
                }
                if (g[i][j] <= lim) {
                    int pk = k;
                    if (pk >= 0) {
                        ll tmp = min(f[pk][i - 1][j], f[pk][i][j - 1]);
                        f[k][i][j] = min(f[k][i][j], tmp);
                    }
                }
            }
        }
    }

    return f[x][n][m];
}

void solve() {
    ll ans = 1e18;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = min(ans, calc(g[i][j]));
        }
    }

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
        cin >> n >> m >> x;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> g[i][j];
            }
        }
        solve();
    }

    return 0;
}