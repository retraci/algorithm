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

const int N = 50010;

int a, b, c, d, k;
int isp[N], pr[N], pc;
int mu[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);
    isp[0] = isp[1] = 0;
    mu[1] = 1;

    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr[++pc] = i;
            mu[i] = -1;
        }

        for (int j = 1; pr[j] <= lim / i; j++) {
            isp[i * pr[j]] = 0;

            if (i % pr[j] == 0) {
                mu[i * pr[j]] = 0;
                break;
            }
            mu[i * pr[j]] = -mu[i];
        }
    }
}

ll calc(int ta, int tb) {
    ta /= k, tb /= k;
    int tt = min(ta, tb);
    ll res = 0;
    for (int i = 1; i <= tt; i++) {
        int j = min({tt, ta / (ta / i), tb / (tb / i)});
        res += 1LL * (mu[j] - mu[i - 1]) * (ta / i) * (tb / i);
        i = j;
    }
    return res;
}

void solve() {
    ll ans = calc(b, d) - calc(a - 1, d) - calc(b, c - 1) + calc(a - 1, c - 1);
    cout << ans << "\n";
}

void prework() {
    prime(50000);
    for (int i = 1; i <= 50000; i++) mu[i] += mu[i - 1];
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
        cin >> a >> b >> c >> d >> k;
        solve();
    }

    return 0;
}