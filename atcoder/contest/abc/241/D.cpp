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

int Q;

void solve() {
    multiset<ll> st;
    while (Q--) {
        ll op, x, y;
        cin >> op;
        if (op == 1) {
            cin >> x;
            st.insert(x);
        } else if (op == 2)  {
            cin >> x >> y;
            auto it = st.upper_bound(x);

            int flag = 0;
            while (y--) {
                if (it == st.begin()) {
                    flag = 1;
                    break;
                }
                it = prev(it);
            }
            if (flag) cout << -1 << "\n";
            else cout << *it << "\n";
        } else {
            cin >> x >> y;
            auto it = st.lower_bound(x);
            y--;

            int flag = 0;
            if (it == st.end()) {
                cout << -1 << "\n";
                continue;
            }
            while (y--) {
                it = next(it);
                if (it == st.end()) {
                    flag = 1;
                    break;
                }
            }
            if (flag) cout << -1 << "\n";
            else cout << *it << "\n";
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
    while (T--) {
        cin >> Q;
        solve();
    }

    return 0;
}