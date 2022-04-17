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

const int N = 2e5 + 10;

ll n, a, b;
ll p[N], s[N];

void solve() {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + p[i];
    ll ans = 0, lst = 0;
    for (int i = 1; i <= n; i++) {
        ll t1 = b * ((s[n] - s[i]) - lst * (n - i));
        ll t2 = a * (p[i] - lst) + b * ((s[n] - s[i]) - p[i] * (n - i));
        if (t2 < t1) lst = p[i];
    }

    ll tar = lst;
    lst = 0;
    for (int i = 1; i <= n; i++) {
        ans += b * (p[i] - lst);
//        debug("bit", b * (p[i] - lst));
        if (p[i] <= tar) {
//            debug("move", a * (p[i] - lst));
            ans += a * (p[i] - lst), lst = p[i];
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
    cin >> T;
    while (T--) {
        cin >> n >> a >> b;
        for (int i = 1; i <= n; i++) cin >> p[i];
        solve();
    }

    return 0;
}