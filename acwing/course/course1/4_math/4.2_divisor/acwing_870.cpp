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

const int N = 110;
const int M = 1e5 + 10;
const int MOD = 1e9 + 7;

// region 质因数分解, 枚举质数
vector<int> isp, pr;

void prime(int lim) {
    isp = vector<int>(lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) pr.push_back(i);

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            if (i % p == 0) break;
        }
    }
}

vector<pll> fs;

void divide(ll x) {
    fs = {};
    for (int p : pr) {
        if (p > x / p) break;

        if (x % p == 0) {
            int c = 0;
            while (x % p == 0) x /= p, c++;
            fs.push_back({p, c});
        }
    }
    if (x > 1) fs.push_back({x, 1});
}
// endregion

int n;
int a[N];

void solve() {
    unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        divide(a[i]);
        for (auto [p, c] : fs) cnt[p] += c;
    }

    ll ans = 1;
    for (auto [_, c] : cnt) {
        ans *= (c + 1);
        ans %= MOD;
    }
    cout << ans << "\n";
}

void prework() {
    prime(1e5);
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}