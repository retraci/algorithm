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

const int N = 2e5 + 10;

int n, m;
int dist[N];

void solve() {
    memset(dist, -1, sizeof dist);

    queue<int> que;
    que.push(n);
    dist[n] = 0;
    while (!que.empty()) {
        int u = que.front(); que.pop();
        if (u == m) {
            cout << dist[u] << "\n";
            return;
        }

        if (u - 1 >= 0 && dist[u - 1] == -1) {
            dist[u - 1] = dist[u] + 1;
            que.push(u - 1);
        }
        if (u + 1 <= 2 * m && dist[u + 1] == -1) {
            dist[u + 1] = dist[u] + 1;
            que.push(u + 1);
        }
        if (u * 2 <= 2 * m && dist[2 * u] == -1) {
            dist[2 * u] = dist[u] + 1;
            que.push(2 * u);
        }
    }
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
        solve();
    }

    return 0;
}