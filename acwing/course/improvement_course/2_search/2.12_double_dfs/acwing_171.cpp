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

const int N = 55;
const int M = 1 << 25;

ll n, w;
ll va[N];
ll vw[M], tt;
ll ans;

ll get(ll x) {
    int left = 0, right = tt - 1;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (vw[mid] <= x) left = mid;
        else right = mid - 1;
    }

    return vw[left];
}

void dfs2(int u, ll s) {
    if (u >= n) {
        ans = max(ans, get(w - s) + s);
        return;
    }

    dfs2(u + 1, s);
    if (s + va[u] <= w) dfs2(u + 1, s + va[u]);
}

void dfs1(int u, ll s) {
    if (u > n / 2) {
        vw[tt++] = s;
        return;
    }

    dfs1(u + 1, s);
    if (s + va[u] <= w) dfs1(u + 1, s + va[u]);
}

void solve() {
    sort(va, va + n, greater<>());

    dfs1(0, 0);
    sort(vw, vw + tt);
    tt = unique(vw, vw + tt) - vw;

    ans = 0;
    dfs2(n / 2 + 1, 0);
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
        cin >> w >> n;
        for (int i = 0; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}