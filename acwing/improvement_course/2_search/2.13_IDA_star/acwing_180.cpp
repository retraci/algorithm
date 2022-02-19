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


const int N = 22;

int n;
int va[N];

int get() {
    int res = 0;
    for (int i = 2; i <= n; i++) {
        res += va[i] - va[i - 1] != 1;
    }

    return (res + 2) / 3;
}

bool dfs(int dep, int mx) {
    if (dep + get() > mx) return false;
    if (get() == 0) return true;

    int bak[n + 1];
    memcpy(bak, va, sizeof bak);
    for (int len = 1; len <= n - 1; len++) {
        for (int L = 1; L + len - 1 <= n; L++) {
            int R = L + len - 1;

            for (int i = R + 1; i <= n; i++) {
                int pos = 1;
                for (int k = 1; k <= L - 1; k++) va[pos++] = bak[k];
                for (int k = R + 1; k <= i; k++) va[pos++] = bak[k];
                for (int k = L; k <= R; k++) va[pos++] = bak[k];
                for (int k = i + 1; k <= n; k++) va[pos++] = bak[k];
                if (dfs(dep + 1, mx)) return true;
            }
        }
    }
    memcpy(va, bak, sizeof bak);

    return false;
}

void solve() {
    int dep = 0;
    while (dep < 5 && !dfs(0, dep)) dep++;

    if (dep >= 5) cout << "5 or more" << "\n";
    else cout << dep << "\n";
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
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}