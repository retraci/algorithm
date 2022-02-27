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

const int N = 1010;

int n;
string g[N];

void solve() {
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            if (j < 6) {
                sum += g[i][j] == '.';
                continue;
            }
            sum += g[i][j] == '.';
            sum -= g[i][j - 6] == '.';

            if (sum <= 2) {
                cout << "Yes" << "\n";
                return;
            }
        }
    }
    for (int j = 1; j <= n; j++) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (i < 6) {
                sum += g[i][j] == '.';
                continue;
            }
            sum += g[i][j] == '.';
            sum -= g[i - 6][j] == '.';

            if (sum <= 2) {
                debug('?');
                cout << "Yes" << "\n";
                return;
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        int sx = i, sy = 1, sum = 0;
        for (int k = 0; ; k++) {
            int nx = sx + k, ny = sy + k;
            if (nx < 1 || nx > n || ny < 1 || ny > n) break;

            if (k < 6) {
                sum += g[nx][ny] == '.';
                continue;
            }
            sum += g[nx][ny] == '.';
            sum -= g[nx - 6][ny - 6] == '.';

            if (sum <= 2) {
                cout << "Yes" << "\n";
                return;
            }
        }
    }

    for (int j = 1; j <= n; j++) {
        int sx = 1, sy = j, sum = 0;
        for (int k = 0; ; k++) {
            int nx = sx + k, ny = sy + k;
            if (nx < 1 || nx > n || ny < 1 || ny > n) break;

            if (k < 6) {
                sum += g[nx][ny] == '.';
                continue;
            }
            sum += g[nx][ny] == '.';
            sum -= g[nx - 6][ny - 6] == '.';

            if (sum <= 2) {
                cout << "Yes" << "\n";
                return;
            }
        }
    }

    for (int j = 1; j <= n; j++) {
        int sx = 1, sy = j, sum = 0;
        for (int k = 0; ; k++) {
            int nx = sx + k, ny = sy - k;
            if (nx < 1 || nx > n || ny < 1 || ny > n) break;

            if (k < 6) {
                sum += g[nx][ny] == '.';
                continue;
            }
            sum += g[nx][ny] == '.';
            sum -= g[nx - 6][ny + 6] == '.';

            if (sum <= 2) {
                cout << "Yes" << "\n";
                return;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int sx = i, sy = n, sum = 0;
        for (int k = 0; ; k++) {
            int nx = sx + k, ny = sy - k;
            if (nx < 1 || nx > n || ny < 1 || ny > n) break;

            if (k < 6) {
                sum += g[nx][ny] == '.';
                continue;
            }
            sum += g[nx][ny] == '.';
            sum -= g[nx - 6][ny + 6] == '.';

            if (sum <= 2) {
                cout << "Yes" << "\n";
                return;
            }
        }
    }

    cout << "No" << "\n";
}

void prework() {
    map<int, vector<int>> a;
    auto it = lower_bound(a[0].begin(), a[0].end(), 3);
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
//        cin >> n;
//        for (int i = 1; i <= n; i++) {
//            cin >> g[i];
//            g[i] = ' ' + g[i];
//        }
//        solve();
    }

    return 0;
}