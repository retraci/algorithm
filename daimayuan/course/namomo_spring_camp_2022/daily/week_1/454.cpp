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

const int N = 2e5 + 10;
const int M = 4e5 + 10;

int n, m;
ti3 es[M];

int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    fa[fx] = fy;
    return true;
}

bool check(int bi, int mask) {
    iota(fa, fa + n + 1, 0);

    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        auto [cost, u, v] = es[i];
        if (cost & mask) continue;
        if (unite(u, v)) cnt++;
    }
    return cnt == n - 1;
}

void solve() {
    sort(es + 1, es + m + 1, [&](auto &a, auto &b) {
        return get<0>(a) < get<0>(b);
    });
    int ans = 0, mask = 0;
    for (int bi = 30; bi >= 0; bi--) {
        mask |= 1 << bi;
        if (!check(bi, mask)) {
            mask -= 1 << bi;
            ans += 1 << bi;
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
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            es[i] = {cost, u, v};
        }
        solve();
    }

    return 0;
}