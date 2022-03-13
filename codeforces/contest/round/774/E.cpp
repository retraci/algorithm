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

ll n, m;

// region 埃筛
int vis[22];

void primes(int lim) {
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (vis[i]) continue;
        for (int j = i; j <= lim / i; j++) vis[i * j] = 1;
    }
}
// endregion

void solve() {
    vector<int> ps;
    for (int i = 2; i <= 20; i++) {
        if (!vis[i]) ps.push_back(i);
    }
    ll ans = (n - 1) * m + 1;
    for (int i = 2; i <= n; i++) {
        while (!ps.empty() && pow(i, ps.back()) > n) ps.pop_back();
        if (ps.empty()) break;

        ll s = 0;
        int lim = 1 << ps.size();
        for (int mask = 1; mask < lim; mask++) {
            int cnt = __builtin_popcount(mask);

            ll tmp = 1;
            for (int j = 0; j < ps.size(); j++) {
                if (mask >> j & 1) tmp *= ps[j];
            }
            if (cnt & 1) s += m / tmp;
            else s -= m / tmp;
        }
        ans -= s;
    }

    cout << ans << "\n";
}

void prework() {
    primes(20);
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
        solve();
    }

    return 0;
}