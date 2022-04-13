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

const int N = 510;
const int dt[4][2] = {{-1, -1}, {-1, 0}, {0, 0}, {0, -1}};
const string mp = "\\/\\/";

int n, m;
string g[N];
int dist[N][N];
int vis[N][N];

int bfs() {
    fill(&dist[0][0], &dist[n][m] + 1, 1e9);
    fill(&vis[0][0], &vis[n][m] + 1, 0);

    deque<pii> que;
    dist[0][0] = 0;
    que.push_back({0, 0});
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop_front();
        if (vis[x][y]) continue;
        vis[x][y] = 1;
        if (x == n && y == m) return dist[n][m];

        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k + 4][0], ny = y + dir[k + 4][1];
            int a = x + dt[k][0], b = y + dt[k][1];

            if (nx >= 0 && nx <= n && ny >= 0 && ny <= m) {
                int cost = g[a][b] != mp[k];

                if (dist[nx][ny] > dist[x][y] + cost) {
                    dist[nx][ny] = dist[x][y] + cost;
                    if (cost == 0) que.push_front({nx, ny});
                    else que.push_back({nx, ny});
                }
            }
        }
    }

    return -1;
}

void solve() {
    if (n + m & 1) {
        cout << "NO SOLUTION" << "\n";
        return;
    }

    cout << bfs() << "\n";
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
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> g[i];
        solve();
    }

    return 0;
}