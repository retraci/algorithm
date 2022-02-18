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

int n;
int g[N][N];
int dist[N][N];
pii pre[N][N];

void solve() {
    memset(dist, -1, sizeof dist);
    queue<pii> que;
    que.push({0, 0});
    dist[0][0] = 0;
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();

        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if (g[nx][ny] == 1 || dist[nx][ny] != -1) continue;
                pre[nx][ny] = {x, y};
                dist[nx][ny] = dist[x][y] + 1;
                que.push({nx, ny});
            }
        }
    }

    vector<pii> ans;
    int tx = n - 1, ty = n - 1;
    ans.push_back({tx, ty});
    while (tx != 0 || ty != 0) {
        tie(tx, ty) = pre[tx][ty];
        ans.push_back({tx, ty});
    }
    reverse(ans.begin(), ans.end());
    for (auto [x, y] : ans) cout << x << " " << y << "\n";
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
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> g[i][j];
            }
        }
        solve();
    }

    return 0;
}