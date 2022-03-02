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

const int N = 1e6 + 10;

int n;
int a[N];

void solve() {
    vector<ll> mil(n + 1), mir(n + 1);
    {
        vector<int> stk;
        a[0] = -1, stk.push_back(0);
        for (int i = 1; i <= n; i++) {
            if (a[stk.back()] >= a[i]) {
                while (a[stk.back()] >= a[i]) stk.pop_back();
                mil[i] = stk.back();
            } else {
                mil[i] = i - 1;
            }
            stk.push_back(i);
        }
    }
    {
        vector<int> stk;
        a[n + 1] = -1, stk.push_back(n + 1);
        for (int i = n; i >= 1; i--) {
            if (a[stk.back()] > a[i]) {
                while (a[stk.back()] > a[i]) stk.pop_back();
                mir[i] = stk.back();
            } else {
                mir[i] = i + 1;
            }
            stk.push_back(i);
        }
    }

    vector<ll> mxl(n + 1), mxr(n + 1);
    {
        vector<int> stk;
        a[0] = 1e9, stk.push_back(0);
        for (int i = 1; i <= n; i++) {
            if (a[stk.back()] <= a[i]) {
                while (a[stk.back()] <= a[i]) stk.pop_back();
                mxl[i] = stk.back();
            } else {
                mxl[i] = i - 1;
            }
            stk.push_back(i);
        }
    }
    {
        vector<int> stk;
        a[n + 1] = 1e9, stk.push_back(n + 1);
        for (int i = n; i >= 1; i--) {
            if (a[stk.back()] < a[i]) {
                while (a[stk.back()] < a[i]) stk.pop_back();
                mxr[i] = stk.back();
            } else {
                mxr[i] = i + 1;
            }
            stk.push_back(i);
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll lsz1 = i - mil[i], rsz1 = mir[i] - i;
        ans += -a[i] * lsz1 * rsz1;

        ll lsz2 = i - mxl[i], rsz2 = mxr[i] - i;
        ans += a[i] * lsz2 * rsz2;
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
        solve();
    }

    return 0;
}