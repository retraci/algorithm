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

int n;
int a[N];

// region 质因数分解, 枚举质数
int isp[M];
vector<int> ps;

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (!isp[i]) continue;

        ps.push_back(i);
        for (int j = i * 2; j <= lim; j += i) isp[j] = 0;
    }
}

vector<pll> fs;

void divide(ll x) {
    fs = {};
    for (int p : ps) {
        if (p > x / p) break;

        if (x % p == 0) {
            int cnt = 0;
            while (x % p == 0) x /= p, cnt++;
            fs.push_back({p, cnt});
        }
    }
    if (x > 1) fs.push_back({x, 1});
}
// endregion

void solve() {
    unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        divide(a[i]);
        for (auto [p, c] : fs) cnt[p] += c;
    }

    ll ans = 1;
    for (auto [p, c] : cnt) {
        ll s = 0, cur = 1;
        for (int i = 0; i <= c; i++) {
            s += cur;
            s %= MOD;

            cur *= p;
            cur %= MOD;
        }
        ans *= s;
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