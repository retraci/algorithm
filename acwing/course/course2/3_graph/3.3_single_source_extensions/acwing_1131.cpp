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

const int N = 11;

int n, m, P;
int es[N][N][N][N];
int g[N][N];

int dij() {
    int lim = 1 << P;
    int dist[n + 1][m + 1][lim], vis[n + 1][m + 1][lim];
    fill(&dist[0][0][0], &dist[n][m][lim - 1] + 1, 1e9), memset(vis, 0, sizeof vis);

    deque<ti4> que;
    que.push_back({0, 1, 1, g[1][1]});
    dist[1][1][g[1][1]] = 0;
    while (!que.empty()) {
        auto [d, x, y, mask] = que.front(); que.pop_front();
        if (vis[x][y][mask]) continue;
        vis[x][y][mask] = 1;

        if (g[x][y]) {
            int ns = mask | g[x][y];
            if (dist[x][y][ns] > dist[x][y][mask]) {
                dist[x][y][ns] = dist[x][y][mask];
                que.push_front({d, x, y, ns});
            }
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                int w = es[x][y][nx][ny];
                if (w == -2 || (w >= 0 && ~mask >> w & 1)) continue;

                if (dist[nx][ny][mask] > dist[x][y][mask] + 1) {
                    dist[nx][ny][mask] = dist[x][y][mask] + 1;
                    que.push_back({-dist[nx][ny][mask], nx, ny, mask});
                }
            }
        }
    }

    return *min_element(&dist[n][m][0], &dist[n][m][lim - 1] + 1);
}

void solve() {
    int ans = dij();
    cout << (ans == 1e9 ? -1 : ans) << "\n";
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
        cin >> n >> m >> P;
        memset(es, -1, sizeof es);

        int cnt;
        cin >> cnt;
        while (cnt--) {
            int x1, y1, x2, y2, x;
            cin >> x1 >> y1 >> x2 >> y2 >> x;
            x--;
            if (x == -1) x = -2;
            es[x1][y1][x2][y2] = es[x2][y2][x1][y1] = x;
        }
        cin >> cnt;
        while (cnt--) {
            int x, y, q;
            cin >> x >> y >> q;
            int mask = 1 << (q - 1);
            g[x][y] |= mask;
        }
        solve();
    }

    return 0;
}