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

const int N = 1e5 + 10;

int n, m, t;
int a[N], b[N];

ll work(int v[], int tt) {
    vector<ll> s(tt + 1, 0);
    for (int i = 1; i <= tt; i++) s[i] = s[i - 1] + v[i];
    if (s[tt] % tt != 0) return -1;

    ll avg = s[tt] / tt;
    vector<int> c(tt + 1, 0);
    for (int i = 2; i <= tt; i++) c[i] = s[i - 1] - (i - 1) * avg;

    nth_element(c.begin() + 1, c.begin() + tt / 2 + 1, c.begin() + tt + 1);
    ll mid = c[tt / 2 + 1];

    ll res = 0;
    for (int i = 1; i <= tt; i++) res += abs(mid - c[i]);
    return res;
}

void solve() {
    ll ret1 = work(a, n), ret2 = work(b, m);

    if (ret1 == -1 && ret2 == -1) {
        cout << "impossible" << "\n";
    } else if (ret1 != -1 && ret2 != -1) {
        cout << "both" << " " << ret1 + ret2 << "\n";
    } else if (ret1 == -1 && ret2 != -1) {
        cout << "column" << " " << ret2 << "\n";
    } else {
        cout << "row" << " " << ret1 << "\n";
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
    while (T--) {
        cin >> n >> m >> t;
        for (int i = 1; i <= t; i++) {
            int x, y;
            cin >> x >> y;
            a[x]++, b[y]++;
        }
        solve();
    }

    return 0;
}