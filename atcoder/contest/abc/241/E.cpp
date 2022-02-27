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

ll n, K;
ll a[N];

void solve() {
    vector<ll> cnt(n, 0), s(n, 0);

    ll u = 0, sum = 0, c = 0;
    while (1) {
        if (cnt[u]) {
            sum += a[u], c++;
            break;
        }

        sum += a[u], c++;
        cnt[u] = c, s[u] = sum;
        u = (u + a[u]) % n;
    }

    ll st = u;
    if (K <= cnt[st]) {
        ll ans = 0, tu = 0;
        while (K--) {
            ans += a[tu];
            tu = (tu + a[tu]) % n;
        }
        cout << ans << "\n";
        return;
    }

    K -= cnt[st];
    ll ans = s[st];

    ll rs = sum - s[st], rc = c - cnt[st];
    ans += rs * (K / rc);
    ll rem = K % rc;
    while (rem--) {
        st = (st + a[st]) % n;
        ans += a[st];
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
        cin >> n >> K;
        for (int i = 0; i < n; i++) cin >> a[i];
        solve();
    }

    return 0;
}