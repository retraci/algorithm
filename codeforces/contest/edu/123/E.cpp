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

ll n;
string str;

void solve() {
    int opr = n - 1, opd = n - 1;
    for (char ch : str) {
        opr -= ch == 'R';
        opd -= ch == 'D';
    }
    if (opr == n - 1 || opd == n - 1) {
        cout << n << "\n";
        return;
    }

    ll ans = n * n;
    ll cr = n - 1, cd = n - 1;
    int fd = 0, fr = 0;
    for (char ch : str) {
        if (ch == 'D') {
            ans -= cr;
        } else {
            cr--;
            if (!fr) {
                fr = 1;
                cr -= opr;
            }
        }
    }
    for (char ch : str) {
        if (ch == 'R') {
            ans -= cd;
        } else {
            cd--;
            if (!fd) {
                fd = 1;
                cd -= opd;
            }
        }
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
    cin >> T;
    while (T--) {
        cin >> n;
        cin >> str;
        solve();
    }

    return 0;
}