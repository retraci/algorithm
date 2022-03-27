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

int n, m, K;
int g[N][N];

int match[N], st[N];

bool dfs(int u) {
    for (int v = 0; v <= m; v++) {
        if (st[v] || !g[u][v]) continue;
        st[v] = 1;

        int t = match[v];
        if (t == -1 || dfs(t)) {
            match[v] = u;
            return true;
        }
    }

    return false;
}

void solve() {
    fill(match, match + m + 1, -1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        fill(st, st + m + 1, 0);
        if (dfs(i)) ans++;
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
    while (cin >> n, n) {
        cin >> m >> K;
        fill(&g[0][0], &g[n][m] + 1, 0);

        for (int i = 1; i <= K; i++) {
            int _, a, b;
            cin >> _ >> a >> b;
            if (a == 0 || b == 0) continue;
            g[a][b] = 1;
        }

        solve();
    }

    return 0;
}