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
const int M = 50 * 1000 + N;

int n;
int a[N];
int f[N][M];

int dfs(int s1, int s2) {
    int &v = f[s1][s2];
    if (v != -1) return v;
    if (s1 == 0) return v = s2 & 1;
    if (s2 == 1) return v = dfs(s1 + 1, 0);

    if (s1 > 0 && !dfs(s1 - 1, s2)) return v = 1;
    if (s2 > 0 && !dfs(s1, s2 - 1)) return v = 1;
    if (s1 >= 2 && !dfs(s1 - 2, s2 + (s2 == 0 ? 2 : 3))) return v = 1;
    if (s1 > 0 && s2 > 0 && !dfs(s1 - 1, s2 + 1)) return v = 1;

    return v = 0;
}

void solve() {
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) s1++;
        else s2 += s2 == 0 ? a[i] : a[i] + 1;
    }

    int ans = dfs(s1, s2);
    cout << (ans ? "YES" : "NO") << "\n";
}

void prework() {
    memset(f, -1, sizeof f);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}