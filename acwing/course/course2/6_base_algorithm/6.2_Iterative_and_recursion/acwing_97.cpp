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

const int MOD = 9901;

int a, b;

int ksm(int p, int c) {
    p %= MOD;
    int res = 1;
    while (c) {
        if (c & 1) res = (res * p) % MOD;
        p = (p * p) % MOD;
        c >>= 1;
    }
    return res;
}

int sum(int p, int c) {
    if (c == 0) return 1;

    int res;
    if (c & 1) {
        res = ((1 + ksm(p, c / 2 + 1)) % MOD
                * sum(p, c / 2) % MOD) % MOD;
    } else {
        res = (((1 + ksm(p, (c - 1) / 2 + 1)) % MOD
                * sum(p, (c - 1) / 2)) % MOD
                        + ksm(p, c)) % MOD;
    }

    return res;
}

void solve() {
    int ans = 1;
    for (int i = 2; i <= a; i++) {
        int cnt = 0;
        while (a % i == 0) {
            cnt++;
            a /= i;
        }
        if (cnt > 0) ans = (ans * sum(i, cnt * b)) % MOD;
    }

    if (a == 0) ans = 0;
    cout << ans << endl;
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
        cin >> a >> b;
        solve();
    }

    return 0;
}