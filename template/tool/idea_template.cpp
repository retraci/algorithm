#[[#includ]]# <iostream>
#[[#includ]]# <cstdio>
#[[#includ]]# <algorithm>
#[[#includ]]# <cstring>
#[[#includ]]# <numeric>
#[[#includ]]# <iomanip>
#[[#includ]]# <vector>
#[[#includ]]# <queue>
#[[#includ]]# <stack>
#[[#includ]]# <set>
#[[#includ]]# <map>
#[[#includ]]# <unordered_set>
#[[#includ]]# <unordered_map>
#[[#includ]]# <bitset>

// region general
#[[#define]]# ll long long
#[[#define]]# ld long double
#[[#define]]# ull unsigned long long
#[[#define]]# fi first
#[[#define]]# se second

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

void solve() {
}

void prework() {
}

int main() {
#[[#ifdef]]# LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#[[#endif]]#

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}