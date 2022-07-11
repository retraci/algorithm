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
int g[N][N];

bool check(int x, int y) {
    int tar = g[x][y] | g[x + 1][y] | g[x][y + 1] | g[x + 1][y + 1];

    return tar != 0
           &&(g[x][y] == 0 || g[x][y] == tar)
           && (g[x + 1][y] == 0 || g[x + 1][y] == tar)
           && (g[x][y + 1] == 0 || g[x][y + 1] == tar)
           && (g[x + 1][y + 1] == 0 || g[x + 1][y + 1] == tar);
}

void solve() {
    queue<ti3> que;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (check(i, j)) que.push({i, j, g[i][j]});
        }
    }

    vector<ti3> ans;
    int vis[n + 1][m + 1];
    memset(vis, 0, sizeof vis);
    while (!que.empty()) {
        auto [x, y, k] = que.front(); que.pop();
        if (vis[x][y]) continue;
        vis[x][y] = 1;
        g[x][y] = g[x + 1][y] = g[x][y + 1] = g[x + 1][y + 1] = 0;
        ans.push_back({x, y, k});

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 1 && nx < n && ny >= 1 && ny < m) {
                    if (check(nx, ny)) {
                        int nk = g[nx][ny] | g[nx + 1][ny] | g[nx][ny + 1] | g[nx + 1][ny + 1];
                        que.push({nx, ny, nk});
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j]) {
                cout << -1 << "\n";
                return;
            }
        }
    }

    cout << ans.size() << "\n";
    reverse(ans.begin(), ans.end());
    for (auto [x, y, k] : ans) cout << x << " " << y << " " << k << "\n";
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
            for (int j = 1; j <= m; j++) {
                cin >> g[i][j];
            }
        }
        solve();
    }

    return 0;
}