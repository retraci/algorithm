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
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1010;

int n, m;
string g[N];
int vis[N][N];

void bfs(int sx, int sy) {
    queue<pii> que;
    que.push({sx, sy});
    vis[sx][sy] = 1;
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();

        for (int k = 0; k < 8; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                if (g[nx][ny] == 'W' && !vis[nx][ny]) {
                    vis[nx][ny] = 1;
                    que.push({nx, ny});
                }
            }
        }
    }
}

void solve() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (vis[i][j] || g[i][j] != 'W') continue;
            ans++;
            bfs(i, j);
        }
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}