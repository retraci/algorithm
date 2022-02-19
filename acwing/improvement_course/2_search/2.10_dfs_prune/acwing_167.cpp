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

const int N = 66;

int n;
int va[N];
int vis[N];

bool dfs(int u, int cur, int st, int mx_len, int cnt) {
    if (u > cnt) return true;
    if (cur == mx_len) return dfs(u + 1, 0, 1, mx_len, cnt);

    for (int i = st; i <= n; i++) {
        if (vis[i]) continue;
        if (cur + va[i] > mx_len) continue;

        vis[i] = 1;
        if (dfs(u, cur + va[i], i + 1, mx_len, cnt)) return true;
        vis[i] = 0;

        if (cur == 0) return false;
        if (cur + va[i] == mx_len) return false;

        int j = i;
        while (j <= n && va[j] == va[i]) j++;
        i = j - 1;
    }

    return false;
}

void solve() {
    int sum = accumulate(va + 1, va + n + 1, 0);

    sort(va + 1, va + n + 1, greater<int>());
    memset(vis, 0, sizeof vis);
    for (int len = va[1]; len <= sum; len++) {
        if (sum % len != 0) continue;

        int cnt = sum / len;
        if (dfs(1, 0, 1, len, cnt)) {
            cout << len << endl;
            break;
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
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}