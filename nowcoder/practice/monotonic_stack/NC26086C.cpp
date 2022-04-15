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

const int N = 5e5 + 10;

int n;
int a[N], p[N];
ll stk[N], s[N], top;

int get_id(int pos) {
    int left = 1, right = top;
    while (left < right) {
        int md = left + right + 1 >> 1;
        if (stk[md] >= pos) left = md;
        else right = md - 1;
    }

    return left;
}

void solve() {
    a[n + 1] = 1e9;

    ll ans = 0;
    stk[++top] = n + 1;
    for (int i = n; i >= 1; i--) {
        while (a[i] >= a[stk[top]]) top--;

        stk[++top] = i;
        int gap = stk[top - 1] - i;
        s[top] = s[top - 1] + 1LL * gap * a[i];

        int id = get_id(p[i]);
        ans += s[id] + 1LL * (stk[id] - p[i]) * a[stk[id + 1]];
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> p[i];
        solve();
    }

    return 0;
}