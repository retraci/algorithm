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
const int MOD = 998244353;

int n;
ll f[N][2];

void solve() {
    ll ans = (f[n][0] + f[n][1]) % MOD;
    cout << ans << "\n";
}

void prework() {
    vector<int> fib(2, 1);
    while (1) {
        int sz = fib.size();
        fib.push_back(fib[sz - 1] + fib[sz - 2]);
        if (fib.back() > 1e7) break;
    }

    int pos = 0;
    for (int i = 1; i <= 1e7; i++) {
        while (fib[pos] <= i) pos++;
        pos--;

        int v1 = fib[pos], v2 = fib[pos - 1];
        f[i][1] = (i - v1 == 0 ? 1 : f[i - v1][0] + f[i - v1][1]) * v1 % MOD;
        if (i - v2 < v2) f[i][0] = (i - v2 == 0 ? 1 : f[i - v2][0] + f[i - v2][1]) * v2 % MOD;
        else f[i][0] = (i - v2 == 0 ? 1 : f[i - v2][0]) * v2 % MOD;
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
        cin >> n;
        solve();
    }

    return 0;
}