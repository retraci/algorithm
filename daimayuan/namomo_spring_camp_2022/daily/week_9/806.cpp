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
pii c[2 * N];

void solve() {
    c[0] = {0, -1};
    for (int i = 1; i <= n; i++) c[i] = {a[i], 0};
    for (int i = 1; i <= n; i++) c[i + n] = {b[i], 1};
    sort(c + 1, c + 2 * n + 1, [](auto &a, auto &b) {
        if (a.fi == b.fi) return a.se > b.se;
        return a.fi < b.fi;
    });

    ll cnt[2] = {0};
    ll mx = max(a[n], b[n]);
    ll ans = 1e18;
    ll cur = 0, lst = 1;
    for (int i = 1; i <= 2 * n; i++) {
        auto [p, ty] = c[i];

        cur += lst * (p - c[i - 1].fi);
        ans = min(ans, cur + 2 * (mx - p));
        cnt[ty]++;
        lst = cnt[1] < cnt[0] ? 3 : 1;
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}