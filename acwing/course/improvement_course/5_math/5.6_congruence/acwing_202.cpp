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

// region 欧拉函数
ll eula(ll x) {
    ll res = x;

    for (ll i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);

    return res;
}
// endregion

ll ksc(ll a, ll b, ll p) {
    a %= p;
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }

    return res;
}

ll ksm(ll a, ll b, ll p) {
    a %= p;
    ll res = 1;
    while (b) {
        if (b & 1) res = ksc(res, a, p);
        a = ksc(a, a, p);
        b >>= 1;
    }

    return res;
}

int ca;
ll L;

void pt(ll ans) {
    static char out[111];
    snprintf(out, 111, "Case %d: %lld", ++ca, ans);
    cout << string(out) << "\n";
}

void solve() {
    ll d = __gcd(L, 8LL);
    ll C = 9 * L / d;

    if (__gcd(10LL, C) != 1) {
        pt(0);
        return;
    }

    ll ans = 1e18;
    ll phi = eula(C);
    for (ll i = 1; i <= phi / i; i++) {
        if (phi % i) continue;

        if (ksm(10, i, C) == 1) ans = min(ans, i);
        if (ksm(10, phi / i, C) == 1) ans = min(ans, phi / i);
    }

    pt(ans);
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
    while (cin >> L, L) {
        solve();
    }

    return 0;
}