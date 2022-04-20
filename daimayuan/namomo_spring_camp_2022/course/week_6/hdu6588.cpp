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

template<class T>
void read(T &x) {
    static char ch;
    static bool neg;
    for (ch = neg = 0; ch < '0' || '9' < ch; neg |= ch == '-', ch = getchar());
    for (x = 0; '0' <= ch && ch <= '9'; (x *= 10) += ch - '0', ch = getchar());
    x = neg ? -x : x;
}

const int N = 1e7 + 10;
const int MOD = 998244353;

// region 积性函数(欧拉筛)
int isp[N];
vector<int> pr;
int low[N], f[N], phi[N];
int s[N];

void prime(int lim) {
    fill(isp, isp + lim + 1, 1);

    phi[1] = f[1] = 1;
    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            low[i] = i;
            // 待修
            phi[i] = i - 1;
            f[i] = 2 * i - 1;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            low[i * p] = p;
            if (i % p == 0) {
                low[i * p] = low[i] * p;
                phi[i * p] = phi[i] * p % MOD;
                // 待修
                if (low[i] == i) {
                    f[i * p] = 1LL * f[i] * p % MOD + phi[i * p];
                    f[i * p] %= MOD;
                } else {
                    f[i * p] = 1LL * f[low[i] * p] * f[i / low[i]] % MOD;
                }
                break;
            }
            f[i * p] = 1LL * f[i] * f[p] % MOD;
            phi[i * p] = 1LL * phi[i] * phi[p] % MOD;
        }
    }
}
// endregion

__int128 n;

int get_m() {
    int left = 1, right = 1e7;
    while (left < right) {
        int md = left + right + 1 >> 1;
        if ((__int128) md * md * md <= n) left = md;
        else right = md - 1;
    }

    return left;
}

int get(int c, int a) {
    int res = 0;
    for (int i = 1; i <= a / i; i++) {
        if (a % i == 0) {
            int j = a / i;
            res += 1LL * phi[i] * (c / i) % MOD;
            res %= MOD;
            if (i != j) {
                res += 1LL * phi[j] * (c / j) % MOD;
                res %= MOD;
            }
        }
    }

    return res;
}

void solve() {
    int m = get_m();
    __int128 cnt = n - (__int128) m * m * m + 1;
    __int128 c = (cnt - 1) / m, r = (cnt - 1) % m;
    int ans = s[m - 1];
    ans += 1LL * (c % MOD) * f[m] % MOD;
    ans %= MOD;
    ans += (m + get(r, m)) % MOD;
    ans %= MOD;
    ans = (ans + MOD) % MOD;
    printf("%d\n", ans);
}

void prework() {
    prime(1e7);

    for (int i = 1; i <= 1e7; i++) {
        int tmp = (1LL * f[i] * (3 * i + 3) % MOD + i) % MOD;
        s[i] = (s[i - 1] + tmp) % MOD;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
//    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    read(T);
//    cin >> T;
    while (T--) {
        read(n);
        solve();
    }

    return 0;
}