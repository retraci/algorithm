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

const int N = 1e4 + 10;
const int MOD = 998244353;

int n, m;
string a;
int b[11];

void solve() {
    n = a.size() - 1;
    for (int i = 1; i <= n; i++) a[i] -= '0';

    int lim = 1 << 10;
    ll f1[2][n + 1][lim], f2[2][n + 1][lim];
    memset(f1, 0, sizeof f1), memset(f2, 0, sizeof f2);
    for (int i = 1; i <= n; i++) {
        for (int d = 1; d <= (i == 1 ? a[i] : 9); d++) {
            int lt = i == 1 && d == a[i];

            f1[lt][i][1 << d] += 1;
            f1[lt][i][1 << d] %= MOD;
            f2[lt][i][1 << d] += d;
            f2[lt][i][1 << d] %= MOD;
        }

        for (int lt = 0; lt <= 1; lt++) {
            for (int mask = 0; mask < lim; mask++) {
                for (int d = 0; d <= (lt ? a[i] : 9); d++) {
                    int nlt = lt && d == a[i];
                    int ns = mask | (1 << d);

                    f1[nlt][i][ns] += f1[lt][i - 1][mask];
                    f1[nlt][i][ns] %= MOD;
                    f2[nlt][i][ns] += f2[lt][i - 1][mask] * 10 + f1[lt][i - 1][mask] * d;
                    f2[nlt][i][ns] %= MOD;
                }
            }
        }
    }

    int tar = 0;
    for (int i = 1; i <= m; i++) tar |= 1 << b[i];
    ll ans = 0;
    for (int lt = 0; lt <= 1; lt++) {
        for (int mask = 0; mask < lim; mask++) {
            if ((mask & tar) == tar) {
                ans += f2[lt][n][mask];
                ans %= MOD;
            }
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
        cin >> a;
        a = ' ' + a;
        cin >> m;
        for (int i = 1; i <= m; i++) cin >> b[i];
        solve();
    }

    return 0;
}