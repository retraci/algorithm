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

int n, m;
string s;

ti3 get_ne(int c1, int c2, int c3) {
    int ne1 = -1, ne2 = -1, ne3 = -1, pos = 0;
    for (int k = 1; k <= n; k++) {
        if (s[k] == 'K') {
            if (c1) {
                c1--;
                continue;
            }
            if (ne1 == -1) ne1 = pos;
            pos++;
        } else if (s[k] == 'E') {
            if (c2) {
                c2--;
                continue;
            }
            if (ne2 == -1) ne2 = pos;
            pos++;
        } else {
            if (c3) {
                c3--;
                continue;
            }
            if (ne3 == -1) ne3 = pos;
            pos++;
        }
    }

    return {ne1, ne2, ne3};
}

void solve() {
    n = s.size() - 1;
    int c1 = 0, c2 = 0, c3 = 0;
    for (int i = 1; i <= n; i++) {
        c1 += s[i] == 'K';
        c2 += s[i] == 'E';
        c3 += s[i] == 'Y';
    }

    m = min(n * n, m);
    ll f[n + 1][m + 1][33][33];
    memset(f, 0, sizeof f);
    f[0][0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int x = 0; x <= c1; x++) {
                for (int y = 0; y <= c2; y++) {
                    int z = i - 1 - x - y;
                    if (z > c3 || z < 0) continue;

                    auto [ne1, ne2, ne3] = get_ne(x, y, z);

                    if (ne1 != -1) {
                        int nj = j + ne1;
                        if (nj <= m) {
                            f[i][nj][x + 1][y] += f[i - 1][j][x][y];
                        }
                    }
                    if (ne2 != -1) {
                        int nj = j + ne2;
                        if (nj <= m) f[i][nj][x][y + 1] += f[i - 1][j][x][y];
                    }
                    if (ne3 != -1) {
                        int nj = j + ne3;
                        if (nj <= m) f[i][nj][x][y] += f[i - 1][j][x][y];
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int j = 0; j <= m; j++) {
        ans += f[n][j][c1][c2];
    }
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
        cin >> s >> m;
        s = ' ' + s;
        solve();
    }

    return 0;
}