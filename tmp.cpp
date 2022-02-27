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

const int N = 85;
int n, K, m, u, v, c, cc[N][N], f[N][N][N][2], i, j, k, nw, ans = 1 << 30;

void solve() {
    memset(cc, 1, sizeof cc);
    scanf("%d%d%d", &n, &K, &m);
    while (m--)scanf("%d%d%d", &u, &v, &c), cc[u][v] = min(cc[u][v], c);
    memset(f[0], 1, sizeof f[0]);
    for (i = 1; i <= n; ++i)f[0][0][i][1] = f[0][i][n + 1][0] = 0;
    while(--K) {
        nw ^= 1; memset(f[nw],1,sizeof f[nw]);
        for (int L = 0; L <= n + 1; L++) {
            for (int R = L + 2; R <= n + 1; R++) {
                for (v = L + 1; v < R; v++) {
                    f[nw][L][v][1]=min(f[nw][L][v][1],min(f[!nw][L][R][1]+cc[R][v],f[!nw][L][R][0]+cc[L][v]));
                    f[nw][v][R][0]=min(f[nw][v][R][0],min(f[!nw][L][R][0]+cc[L][v],f[!nw][L][R][1]+cc[R][v]));
                }
            }
        }
    }
    for (i = 0; i <= n + 1; ++i)for (j = 0; j <= n + 1; ++j)ans = min(ans, min(f[nw][i][j][0], f[nw][i][j][1]));
    if (ans > 1 << 20)ans = -1;
    printf("%d\n", ans);
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
        solve();
    }

    return 0;
}