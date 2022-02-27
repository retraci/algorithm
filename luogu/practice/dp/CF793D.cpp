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

int n, K, m;
int g[N][N];

void solve() {
    int f[K + 1][n + 2][n + 2][2];
    fill(&f[0][0][0][0], &f[K][n + 1][n + 1][1] + 1, 1e9);
    for (int i = 1; i <= n; i++) f[1][0][i][1] = f[1][i][n + 1][0] = 0;

    for (int k = 1; k < K; k++) {
        for (int L = 0; L <= n + 1; L++) {
            for (int R = L + 2; R <= n + 1; R++) {
                for (int v = L + 1; v < R; v++) {
                    f[k + 1][L][v][1] = min(f[k + 1][L][v][1], f[k][L][R][1] + g[R][v]);
                    f[k + 1][v][R][0] = min(f[k + 1][v][R][0], f[k][L][R][1] + g[R][v]);

                    f[k + 1][L][v][1] = min(f[k + 1][L][v][1], f[k][L][R][0] + g[L][v]);
                    f[k + 1][v][R][0] = min(f[k + 1][v][R][0], f[k][L][R][0] + g[L][v]);
                }
            }
        }
    }

    int ans = *min_element(&f[K][0][0][0], &f[K][n + 1][n + 1][1] + 1);
    cout << (ans == 1e9 ? -1: ans) << "\n";
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
        cin >> n >> K >> m;
        memset(g, 0x3f, sizeof g);

        while (m--) {
            int u, v, cost;
            cin >> u >> v >> cost;
            g[u][v] = min(g[u][v], cost);
        }
        solve();
    }

    return 0;
}