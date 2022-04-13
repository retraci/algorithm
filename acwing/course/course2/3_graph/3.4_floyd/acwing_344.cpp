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

const int N = 110;

int n, m;
int g[N][N];
int f[N][N];
int pre[N][N];

int mi;
vector<int> path;

void dfs(int i, int j) {
    if (pre[i][j] == 0) return;

    int k = pre[i][j];
    dfs(i, k);
    path.push_back(k);
    dfs(k, j);
}

void floyd() {
    mi = 1e9;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (mi > 1LL * g[k][i] + f[i][j] + g[j][k]) {
                    mi = g[k][i] + f[i][j] + g[j][k];

                    path = {};
                    path.push_back(k);
                    path.push_back(i);
                    dfs(i, j);
                    path.push_back(j);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (f[i][j] > f[i][k] + f[k][j]) {
                    f[i][j] = f[i][k] + f[k][j];
                    pre[i][j] = k;
                }
            }
        }
    }
}

void solve() {
    memcpy(f, g, sizeof f);

    floyd();

    if (mi == 1e9) {
        cout << "No solution." << "\n";
        return;
    }
    for (int x : path) cout << x << " ";
    cout << "\n";
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
        fill(&g[0][0], &g[n][n] + 1, 1e9);
        for (int i = 1; i <= n; i++) g[i][i] = 0;

        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            g[u][v] = g[v][u] = min(g[u][v], cost);
        }
        solve();
    }

    return 0;
}