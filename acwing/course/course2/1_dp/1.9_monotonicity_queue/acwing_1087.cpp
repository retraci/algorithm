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
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1e5 + 10;

int n, m;
int va[N];
ll s[N];
ll f[N];

ll get(int x) {
    if (x == 0) return 0;
    return f[x - 1] - s[x];
}

void solve() {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + va[i];

    deque<int> que;
    que.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (i - que.front() > m) que.pop_front();
        f[i] = max(f[i - 1], s[i] + get(que.front()));
        while (!que.empty() && get(que.back()) <= get(i)) que.pop_back();
        que.push_back(i);
    }
    cout << f[n] << "\n";
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
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}