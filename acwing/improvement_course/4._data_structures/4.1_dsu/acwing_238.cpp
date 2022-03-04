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

const int N = 30010;

int n;
int fa[N], sz[N], d[N];

int find(int x) {
    if (x == fa[x]) return x;
    int rt = find(fa[x]);
    d[x] += d[fa[x]];
    return fa[x] = rt;
}

bool unite(int x, int y, int cost) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    d[fx] = cost;
    sz[fy] += sz[fx];
    fa[fx] = fy;
    return true;
}

void solve() {
    iota(fa, fa + N, 0);
    fill(sz, sz + N, 1);

    while (n--) {
        string op;
        int x, y;
        cin >> op >> x >> y;

        if (op == "M") {
            unite(x, y, sz[find(y)]);
        } else {
            int fx = find(x), fy = find(y);
            if (fx != fy) cout << -1 << "\n";
            else cout << max(0, abs(d[x] - d[y]) - 1) << "\n";
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
        cin >> n;
        solve();
    }

    return 0;
}