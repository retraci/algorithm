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

const int N = 5e5 + 10;

int n, m;
ll a[N], s[N];
ll stk[N], lst[N], h[N], tp;

ll get(int id, ll delta, ll pre) {
    ll cur = delta * a[id] + pre;
    return cur;
}

void solve() {
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    tp = 0;
    stk[++tp] = 0, lst[tp] = 0, h[tp] = 0;
    stk[++tp] = 1, lst[tp] = 0, h[tp] = 0;
    for (int _ = 1; _ <= m; _++) {
        ll d, b;
        cin >> d >> b;

        ll ans = 0, rb = n;
        while (get(stk[tp], d - lst[tp], h[tp]) > b) {
            int lb = stk[tp];
            ll cnt = rb - lb + 1;
            ans += (s[rb] - s[lb - 1]) * (d - lst[tp]) + cnt * (h[tp] - b);
            rb = lb - 1, tp--;
        }

        if (get(rb, d - lst[tp], h[tp]) > b) {
            int left = stk[tp], right = rb;
            while (left < right) {
                int md = left + right >> 1;
                if (get(md, d - lst[tp], h[tp]) >= b) right = md;
                else left = md + 1;
            }
            int lb = left;
            ll cnt = rb - lb + 1;
            ans += (s[rb] - s[lb - 1]) * (d - lst[tp]) + cnt * (h[tp] - b);

            stk[++tp] = lb, lst[tp] = d, h[tp] = b;
        } else if (rb + 1 <= n) {
            stk[++tp] = rb + 1, lst[tp] = d, h[tp] = b;
        }

        cout << ans << "\n";
    }
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
        solve();
    }

    return 0;
}