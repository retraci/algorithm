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

int n = 5;
char a[8][8], flip[8][8];

void solve() {
    int lim = 1 << 5;

    int ans = 7;
    for (int mask = 0; mask < lim; mask++) {
        int cnt = 0;
        memset(flip, 0, sizeof(flip));
        for (int i = 1; i <= n; i++) {
            if (mask >> (i - 1) & 1) {
                cnt++;
                flip[1][i] = 1;
            }
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int c = a[i - 1][j] + flip[i - 1][j] + flip[i - 1][j - 1] + flip[i - 1][j + 1] + flip[i - 2][j];
                if (c & 1) continue;
                flip[i][j] = 1;
                cnt++;
            }
        }

        int flag = 0;
        for (int j = 1; j <= n; j++) {
            int c = a[n][j] + flip[n][j] + flip[n][j - 1] + flip[n][j + 1] + flip[n - 1][j];
            if (c & 1) continue;

            flag = 1;
            break;
        }

        if (!flag) ans = min(ans, cnt);
    }

    cout << (ans > 6 ? -1 : ans) << "\n";
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
    cin >> T;
    while (T--) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
                a[i][j] -= '0';
            }
        }

        solve();
    }

    return 0;
}