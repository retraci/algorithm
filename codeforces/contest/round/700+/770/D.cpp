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

const int N = 1010;

int n;

void resp(int x, int y) {
    cout << "! " << x << " " << y << "\n";
    cout.flush();
}

int ask(int x, int y, int z) {
    cout << "? " << x << " " << y << " " << z << "\n";
    cout.flush();
    int res;
    cin >> res;
    return res;
}

void solve() {
    map<int, int> mp;
    for (int i = 3; i <= n; i++) mp[ask(1, 2, i)] = i;

    if (mp.size() == 1) {
        int q1 = ask(3, 4, 1), q2 = ask(3, 4, 2);
        int x = mp.begin()->fi;
        if (q1 < x && q2 < x) {
            resp(1, 2);
            return;
        }
        if (q1 > x || q2 > x) {
            resp(3, 4);
            return;
        }

        mp = {};
        for (int i = 1; i <= n; i++) {
            if (i == 3 || i == 4) continue;
            mp[ask(3, 4, i)] = i;
        }
        if (mp.size() == 1) {
            resp(3, 4);
        } else {
            resp(mp.rbegin()->se, mp.rbegin()->se);
        }
    } else {
        int id = mp.rbegin()->se;

        mp = {};
        for (int i = 2; i <= n; i++) {
            if (i == id) continue;
            mp[ask(1, id, i)] = i;
        }
        if (mp.size() == 1) {
            resp(1, id);
        } else {
            resp(id, mp.rbegin()->se);
        }
    }
}

void prework() {
}

int main() {
//#ifdef LOCAL
//    freopen("../in.txt", "r", stdin);
//    freopen("../out.txt", "w", stdout);
//#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}