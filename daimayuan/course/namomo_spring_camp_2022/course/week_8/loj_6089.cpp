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
#include <cmath>

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

const int MOD = 23333333;

int n;

void solve() {
    int m = sqrt(n);
    int f[n + 1], s[n + 1];
    memset(f, 0, sizeof f);
    f[0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < i; j++) s[j] = f[j];
        for (int j = i; j <= n; j++) s[j] = (s[j - i] + f[j]) % MOD;

        for (int j = 0; j <= n; j++) {
            if (j - (i + 1) * i >= 0) f[j] = s[j] - s[j - (i + 1) * i];
            else f[j] = s[j];
            f[j] = (f[j] + MOD) % MOD;
        }
    }

    int g[m + 1][n + 1];
    memset(g, 0, sizeof g);
    for (int j = 0; j <= n; j++) g[0][j] = f[j];
    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= n; j++) {
            g[i][j] += g[i - 1][j - (m + 1)];
            g[i][j] %= MOD;
            g[i][j] += g[i][j - i];
            g[i][j] %= MOD;
        }
    }

    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans += g[i][n];
        ans %= MOD;
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
        solve();
    }

    return 0;
}