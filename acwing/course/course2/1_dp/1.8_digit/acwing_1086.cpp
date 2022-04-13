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
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 22;
const ll MOD = 1e9 + 7;

ll L, R;
tl3 f[N][10][7][7];

tl3 get(int i, int j, int a, int b) {
    ll t = 0, s1 = 0, s2 = 0;
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            if (x == a || y == b) continue;

            auto &[t1, t2, t3] = f[i][j][x][y];
            t += t1, s1 += t2, s2 += t3;
            t %= MOD, s1 %= MOD, s2 %= MOD;
        }
    }

    return {t, s1, s2};
}

ll work(ll n) {
    if (n == 0) return 0;

    vector<int> va;
    while (n) va.push_back(n % 10), n /= 10;

    ll pow = 1;
    for (int i = 1; i <= va.size(); i++) pow *= 10;

    ll res = 0, lsta = 0, lstb = 0;
    for (int i = va.size() - 1; i >= 0; i--, pow /= 10) {
        int x = va[i];

        for (int j = 0; j < x; j++) {
            if (j == 7) continue;

            int a = ((-lsta % 7) * (pow % 7) % 7 + 7) % 7;
            int b = ((-lstb % 7) + 7) % 7;
            auto [t, s1, s2] = get(i + 1, j, a, b);

            res += s2
                   + ((lsta % MOD) * (pow % MOD) % MOD) * ((lsta % MOD) * (pow % MOD) % MOD) % MOD * t % MOD
                   + 2 * (lsta % MOD) % MOD * (pow % MOD) % MOD * s1 % MOD;
            res %= MOD;
        }

        if (x == 7) break;
        lsta = lsta * 10 + x;
        lstb += x;

        if (i == 0 && lsta % 7 != 0 && lstb % 7 != 0) {
            lsta %= MOD;
            res += lsta * lsta;
            res %= MOD;
        }
    }

    return res;
}

void solve() {
    ll ans = (work(R) - work(L - 1) + MOD) % MOD;
    cout << ans << "\n";
}

void prework() {
    for (int i = 0; i <= 9; i++) {
        if (i == 7) continue;
        f[1][i][i % 7][i % 7] = {1, i, i * i};
    }

    ll pow = 10;
    for (int i = 2; i < N; i++, pow *= 10) {
        for (int j = 0; j <= 9; j++) {
            if (j == 7) continue;
            for (int a = 0; a < 7; a++) {
                for (int b = 0; b < 7; b++) {
                    for (int k = 0; k <= 9; k++) {
                        if (k == 7) continue;

                        int pa = (a - j * (pow % 7) % 7 + 7) % 7, pb = (b - j % 7 + 7) % 7;
                        auto &[t, s1, s2] = f[i - 1][k][pa][pb];
                        auto &[nt, ns1, ns2] = f[i][j][a][b];
                        nt += t;
                        ns1 += s1 + j * (pow % MOD) % MOD * t % MOD;
                        ns2 += s2
                               + (j * (pow % MOD) % MOD) * (j * (pow % MOD) % MOD) % MOD * t % MOD
                               + 2 * j % MOD * (pow % MOD) % MOD * s1 % MOD;
                        nt %= MOD, ns1 %= MOD, ns2 %= MOD;
                    }
                }
            }
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
        cin >> L >> R;
        solve();
    }

    return 0;
}