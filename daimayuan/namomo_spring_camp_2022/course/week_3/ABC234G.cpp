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

const int N = 3e5 + 10;
const int MOD = 998244353;

int n;
int a[N];

void solve() {
    vector<int> stk1, stk2;
    vector<int> f(n + 1, 0), fmx(n + 1), fmi(n + 1);
    f[0] = 1;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        fmx[i] = fmi[i] = f[i - 1];
        while (!stk1.empty() && a[stk1.back()] <= a[i]) {
            int id = stk1.back(); stk1.pop_back();
            fmx[i] += fmx[id];
            fmx[i] %= MOD;
            cur -= 1LL * fmx[id] * a[id] % MOD;
            cur %= MOD;
        }
        while (!stk2.empty() && a[stk2.back()] >= a[i]) {
            int id = stk2.back(); stk2.pop_back();
            fmi[i] += fmi[id];
            fmi[i] %= MOD;
            cur += 1LL * fmi[id] * a[id] % MOD;
            cur %= MOD;
        }

        cur += 1LL * fmx[i] * a[i] % MOD;
        cur %= MOD;
        cur -= 1LL * fmi[i] * a[i] % MOD;
        cur %= MOD;
        f[i] = cur;

        stk1.push_back(i), stk2.push_back(i);
    }

    int ans = (f[n] + MOD) % MOD;
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}