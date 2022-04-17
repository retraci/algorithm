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

int a, b;
int isp[N], pr[N], pc;
int mu[N];
ll h[N];

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

void solve() {
    ll ans = 0;
    int tt = min(a, b);
    for (int i = 1; i <= tt; i++) {
        int j = min({tt, a / (a / i), b / (b / i)});
        ans += 1LL * (mu[j] - mu[i - 1]) * h[a / i] * h[b / i];
        i = j;
    }
    cout << ans << "\n";
}

void prework() {
    prime(50000);
    for (int i = 1; i <= 50000; i++) mu[i] += mu[i - 1];

    for (int x = 1; x <= 50000; x++) {
        for (int i = 1; i <= x; i++) {
            int j = min(x, x / (x / i));
            h[x] += 1LL * (j - i + 1) * (x / i);
            i = j;
        }
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
    cin >> T;
    while (T--) {
        cin >> a >> b;
        solve();
    }

    return 0;
}