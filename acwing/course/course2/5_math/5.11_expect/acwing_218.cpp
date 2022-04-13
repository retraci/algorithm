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

int a, b, c, d;
double f[14][14][14][14][5][5];

double dfs(int c1, int c2, int c3, int c4, int x, int y) {
    double &v = f[c1][c2][c3][c4][x][y];
    if (v != -1) return v;

    int s1 = c1 + (x == 1) + (y == 1);
    int s2 = c2 + (x == 2) + (y == 2);
    int s3 = c3 + (x == 3) + (y == 3);
    int s4 = c4 + (x == 4) + (y == 4);
    if (s1 >= a && s2 >= b && s3 >= c && s4 >= d) return v = 0;
    if (c1 > 13 || c2 > 13 || c3 > 13 || c4 > 13) return v = 1e9;

    int sum = 54 - c1 - c2 - c3 - c4 - (x != 0) - (y != 0);
    double res = 1;
    if (c1 < 13) res += 1.0 * (13 - c1) / sum * dfs(c1 + 1, c2, c3, c4, x, y);
    if (c2 < 13) res += 1.0 * (13 - c2) / sum * dfs(c1, c2 + 1, c3, c4, x, y);
    if (c3 < 13) res += 1.0 * (13 - c3) / sum * dfs(c1, c2, c3 + 1, c4, x, y);
    if (c4 < 13) res += 1.0 * (13 - c4) / sum * dfs(c1, c2, c3, c4 + 1, x, y);
    if (x == 0) {
        double tmp = 1e9;
        for (int i = 1; i <= 4; i++) {
            tmp = min(tmp, dfs(c1, c2, c3, c4, i, y));
        }
        res += 1.0 / sum * tmp;
    }
    if (y == 0) {
        double tmp = 1e9;
        for (int i = 1; i <= 4; i++) {
            tmp = min(tmp, dfs(c1, c2, c3, c4, x, i));
        }
        res += 1.0 / sum * tmp;
    }

    return v = res;
}

void solve() {
    fill(&f[0][0][0][0][0][0], &f[13][13][13][13][4][4] + 1, -1);
    double ans = dfs(0, 0, 0, 0, 0, 0);
    if (ans > 54) {
        cout << "-1.000" << "\n";
        return;
    }
    cout << fixed << setprecision(3);
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
        cin >> a >> b >> c >> d;
        solve();
    }

    return 0;
}