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

const int N = 310;
const int MOD = 998244353;

int n, m;
int a[N], b[N];

void solve() {
    vector<int> c(n + 1, 0);
    for (int i = 1; i <= n; i++) c[a[i]] = i;

    int f[n + 1][m + 1][n + 2];
    memset(f, 0, sizeof f);
    f[0][0][n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        int rk = b[c[i]];
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= n + 1; k++) {
                if (j + 1 <= m && k >= rk) {
                    f[i][j + 1][k] += f[i - 1][j][k];
                    f[i][j + 1][k] %= MOD;
                }

                f[i][j][min(k, rk)] += f[i - 1][j][k];
                f[i][j][min(k, rk)] %= MOD;
            }
        }
    }

    int ans = 0;
    for (int k = 0; k <= n + 1; k++) ans += f[n][m][k], ans %= MOD;
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}