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

const int N = 1e6 + 10;

ll n, P;
int isp[2 * N], ps[2 * N], cnt;

ll ksm(ll a, ll b) {
    a %= P;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % P;
        a = a * a % P;
        b >>= 1;
    }

    return res;
}

ll get(ll a, ll p) {
    ll res = 0, cur = p;
    while (cur <= a) {
        res += a / cur;
        cur *= p;
    }

    return res;
}

ll C(ll a, ll b) {
    ll res = 1;

    for (int i = 1; i <= cnt; i++) {
        int p = ps[i];
        if (p > a) break;
        ll c = get(a, p) - get(a - b, p) - get(b, p);
        res *= ksm(p, c);
        res %= P;
    }

    return res;
}

void solve() {
    ll ans = C(2 * n, n) - C(2 * n, n - 1);
    ans = (ans + P) % P;
    cout << ans << "\n";
}

void prework() {
    fill(isp + 1, isp + (int) 2e6 + 1, 1);
    isp[0] = isp[1] = 0;
    for (int i = 2; i <= 2e6; i++) {
        if (!isp[i]) continue;

        ps[++cnt] = i;
        for (int j = i; j <= 2e6; j += i) isp[j] = 0;
    }
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
        cin >> n >> P;
        solve();
    }

    return 0;
}