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

const int N = 1e7 + 10;
const int MOD = 20101009;

int n, m;

// region 积性函数(欧拉筛)
int isp[N];
int pr[N], pc;
int h[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    h[1] = 1;
    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr[++pc] = i;
            h[i] = (i - 1LL * i * i % MOD + MOD) % MOD;
        }

        for (int j = 1; pr[j] <= lim / i; j++) {
            isp[i * pr[j]] = 0;
            if (i % pr[j] == 0) {
                h[i * pr[j]] = 1LL * h[i] * pr[j] % MOD;
                break;
            }
            h[i * pr[j]] = 1LL * h[i] * h[pr[j]] % MOD;
        }
    }
}
// endregion

void solve() {
    ll ans = 0;
    int tt = min(n, m);
    for (int i = 1; i <= tt; i++) {
        int j = min({tt, n / (n / i), m / (m / i)});
        ll a = 1LL * (1 + n / i) * (n / i) / 2 % MOD;
        ll b = 1LL * (1 + m / i) * (m / i) / 2 % MOD;
        ll tmp = a * b % MOD;
        ans += 1LL * (h[j] - h[i - 1]) * tmp % MOD;
        ans = (ans % MOD + MOD) % MOD;
        i = j;
    }
    cout << ans << "\n";
}

void prework() {
    prime(1e7);

    for (int i = 1; i <= 1e7; i++) {
        h[i] += h[i - 1];
        h[i] %= MOD;
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
        cin >> n >> m;
        solve();
    }

    return 0;
}