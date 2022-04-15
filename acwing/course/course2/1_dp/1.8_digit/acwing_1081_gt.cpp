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

const int N = 33;

ll L, R, K, B;

ll work(int num) {
    vector<int> a;
    while (num) a.push_back(num % B), num /= B;
    a.push_back(0);
    reverse(a.begin(), a.end());
    int n = a.size() - 1;

    ll f[2][n + 1][K + 2];
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int d = 1; d <= (i == 1 ? a[i] : B - 1); d++) {
            if (d > 1) break;

            int lt = i == 1 && d == a[i];
            f[lt][i][d == 1] += 1;
        }

        for (int lt = 0; lt <= 1; lt++) {
            for (int j = 0; j <= K; j++) {
                for (int d = 0; d <= (lt ? a[i] : B - 1); d++) {
                    if (d > 1) break;

                    int nlt = lt && d == a[i];
                    if (d == 1) f[nlt][i][j + 1] += f[lt][i - 1][j];
                    else f[nlt][i][j] += f[lt][i - 1][j];
                }
            }
        }
    }

    ll res = f[0][n][K] + f[1][n][K];
    return res;
}

void solve() {
    cout << work(R) - work(L - 1) << "\n";
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
        cin >> L >> R >> K >> B;
        solve();
    }

    return 0;
}