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

const int N = 100010;

int n, m;
int a[N], b[N], c[N];

void solve() {
    vector<int> d[n + 1];
    vector<int> e(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) d[b[i]].push_back(i);
        e[b[i]] = i;
    }

    int lst = 0;
    vector<int> ans(m + 1);
    for (int i = m; i >= 1; i--) {
        int co = c[i];
        if (d[co].empty()) {
            if (!lst && !e[co]) {
                cout << "NO" << "\n";
                return;
            }

            ans[i] = lst ? lst : e[co];
            lst = ans[i];
        } else {
            int cur = d[co].back(); d[co].pop_back();
            ans[i] = cur, lst = ans[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!d[i].empty()) {
            cout << "NO" << "\n";
            return;
        }
    }

    cout << "YES" << "\n";
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= m; i++) cin >> c[i];
        solve();
    }

    return 0;
}