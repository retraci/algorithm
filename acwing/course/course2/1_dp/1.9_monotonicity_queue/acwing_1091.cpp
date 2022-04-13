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

int n, m, k;
int g[N][N];

void solve() {
    int va[n + 1][m + 1], vb[n + 1][m + 1];
    for (int i = 1; i <= n; i++) {
        deque<int> que1, que2;
        for (int j = 1; j <= m; j++) {
            while (!que1.empty() && j - que1.front() + 1 > k) que1.pop_front();
            while (!que2.empty() && j - que2.front() + 1 > k) que2.pop_front();
            while (!que1.empty() && g[i][que1.back()] <= g[i][j]) que1.pop_back();
            while (!que2.empty() && g[i][que2.back()] >= g[i][j]) que2.pop_back();
            que1.push_back(j), que2.push_back(j);

            va[i][j] = g[i][que1.front()], vb[i][j] = g[i][que2.front()];
        }
    }

    int vc[n + 1][m + 1], vd[n + 1][m + 1];
    for (int j = 1; j <= m; j++) {
        deque<int> que1, que2;
        for (int i = 1; i <= n; i++) {
            while (!que1.empty() && i - que1.front() + 1 > k) que1.pop_front();
            while (!que2.empty() && i - que2.front() + 1 > k) que2.pop_front();
            while (!que1.empty() && va[que1.back()][j] <= va[i][j]) que1.pop_back();
            while (!que2.empty() && vb[que2.back()][j] >= vb[i][j]) que2.pop_back();
            que1.push_back(i), que2.push_back(i);

            vc[i][j] = va[que1.front()][j], vd[i][j] = vb[que2.front()][j];
        }
    }

    int ans = 1e9;
    for (int i = k; i <= n; i++) {
        for (int j = k; j <= m; j++) {
            ans = min(ans, vc[i][j] - vd[i][j]);
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
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> g[i][j];
            }
        }
        solve();
    }

    return 0;
}