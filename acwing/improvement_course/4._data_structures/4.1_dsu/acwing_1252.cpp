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

const int N = 10010;
const int M = 5010;

int n, m, W;
int v[N], w[N];
pii a[M];

int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    v[y] += v[x], w[y] += w[x];
    return true;
}

void solve() {
    iota(fa, fa + n + 1, 0);
    for (int i = 1; i <= m; i++) {
        auto [tu, tv] = a[i];
        unite(tu, tv);
    }

    vector<int> f(W + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (i != find(i)) continue;

        for (int j = W; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    cout << f[W] << "\n";
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
        cin >> n >> m >> W;

        for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];
        for (int i = 1; i <= m; i++) cin >> a[i].fi >> a[i].se;

        solve();
    }

    return 0;
}