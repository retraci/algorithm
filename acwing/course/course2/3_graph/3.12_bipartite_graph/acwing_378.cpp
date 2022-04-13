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
//using namespace grid_delta;

const int dir[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

const int N = 110;

int n, m, P;
int g[N][N];

pii match[N][N];
int st[N][N];

bool dfs(int x, int y) {
    for (int k = 0; k < 8; k++) {
        int ta = x + dir[k][0], tb = y + dir[k][1];
        if (ta >= 1 && ta <= n && tb >= 1 && tb <= m) {
            if (st[ta][tb] || g[ta][tb]) continue;
            st[ta][tb] = 1;

            auto [tx, ty] = match[ta][tb];
            if (tx == 0 || dfs(tx, ty)) {
                match[ta][tb] = {x, y};
                return true;
            }
        }
    }

    return false;
}

void solve() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i + j & 1 && !g[i][j]) {
                fill(&st[0][0], &st[n][m] + 1, 0);
                if (dfs(i, j)) cnt++;
            }
        }
    }

    int ans = n * m - P - cnt;
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
        cin >> n >> m >> P;
        fill(&g[0][0], &g[n][m] + 1, 0);

        for (int i = 1; i <= P; i++) {
            int x, y;
            cin >> x >> y;
            g[x][y] = 1;
        }

        solve();
    }

    return 0;
}