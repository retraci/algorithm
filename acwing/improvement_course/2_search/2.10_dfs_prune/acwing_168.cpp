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
#include <cmath>

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

const int N = 22;

int n, m;
int miv[N], mis[N];
int rs[N], hs[N];
int ans;

void dfs(int dep, int v, int s) {
    if (v + miv[dep] > n) return;
    if (s + mis[dep] >= ans) return;
    if (s + 2 * (n - v) / rs[dep + 1] >= ans) return;

    if (dep == 0) {
        if (v == n) ans = min(ans, s);
        return;
    }

    int mxr = min((int) sqrt(n - v), rs[dep + 1] - 1);
    for (int r = mxr; r >= dep; r--) {
        int mxh = min((int) (n - v) / r / r, hs[dep + 1] - 1);

        for (int h = mxh; h >= dep; h--) {
            int nv = v + r * r * h;
            int ns = s + 2 * r * h;

            if (dep == m) ns += r * r;
            rs[dep] = r, hs[dep] = h;
            dfs(dep - 1, nv, ns);
        }
    }
}

void init() {
    for (int i = 1; i <= m; i++) {
        miv[i] = miv[i - 1] + i * i * i;
        mis[i] = mis[i - 1] + 2 * i * i;
    }

    rs[m + 1] = hs[m + 1] = 1e9;
}

void solve() {
    init();

    ans = 1e9;
    dfs(m, 0, 0);

    cout << (ans == 1e9 ? 0 : ans) << endl;
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