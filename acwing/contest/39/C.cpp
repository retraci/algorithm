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

int n;
int va[N];

int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return false;
    fa[tx] = ty;
    return true;
}

void solve() {
    iota(fa, fa + n + 1, 0);

    vector<int> vb[26];
    for (int i = 0; i < 26; i++) {
        for (int j = 1; j <= n; j++) {
            int mask = va[j];
            if (mask >> i & 1) vb[i].push_back(j);
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 1; j < vb[i].size(); j++) {
            unite(vb[i][0], vb[i][j]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += find(i) == i;
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
        cin >> n;
        for (int i = 1; i <= n; i++) {
            string str;
            cin >> str;
            int mask = 0;
            for (char ch : str) {
                mask |= 1 << (ch - 'a');
            }
            va[i] = mask;
        }
        solve();
    }

    return 0;
}