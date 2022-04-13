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
const ll MOD = 1e9 + 7;

ll n, m;
ll a[N];

ll ksm(ll ta, ll tb) {
    ta %= MOD;

    ll res = 1;
    while (tb) {
        if (tb & 1) res = res * ta % MOD;
        ta = ta * ta % MOD;
        tb >>= 1;
    }

    return res;
}

ll inv(ll ta) {
    return ksm(ta, MOD - 2);
}

ll C(ll ta, ll tb) {
    if (ta < 0 || tb < 0 || tb > ta) return 0;

    ll up = 1, down = 1;
    for (int i = 1; i <= tb; i++) {
        down *= i;
        up *= (ta - i + 1) % MOD;
        down %= MOD, up %= MOD;
    }

    return up * inv(down) % MOD;
}

void solve() {
    ll ans = C(n + m - 1, n - 1);
    int lim = 1 << n;
    for (int mask = 1; mask < lim; mask++) {
        ll sign = 1, sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                sign *= -1;
                sum += a[i] + 1;
            }
        }
        ans += sign * C(m + n - 1 - sum, n - 1);
        ans %= MOD;
    }

    ans = (ans + MOD) % MOD;
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
        for (int i = 0; i < n; i++) cin >> a[i];
        solve();
    }

    return 0;
}