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

const int N = 3e5 + 10;

int n, m, C;
ll c[N], w1[N], w2[N];
ll nc[N], nw[N];

void solve() {
    vector<ll> mx(C + 1, 0), id(C + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (mx[c[i]] < w1[i]) {
            mx[c[i]] = w1[i];
            id[c[i]] = i;
        }
    }

    vector<int> upd[C + 1];
    int nl = 0;
    for (int i = 1; i <= C; i++) {
        int pos = id[i];
        if (pos == 0) continue;

        nl++;
        nc[nl] = c[pos], nw[nl] = w1[pos];

        for (int j = nc[nl]; j <= C; j += nc[nl]) {
            upd[j].push_back(nl);
        }
    }

    vector<ll> f(C + 1, 0);
    for (int i = 1; i <= C; i++) {
        f[i] = f[i - 1];

        for (int j : upd[i]) {
            f[i] = max(f[i], 1LL * i / nc[j] * nw[j]);
        }
    }

    for (int i = 1; i <= m; i++) {
        int pos = upper_bound(f.begin(), f.end(), w2[i]) - f.begin();
        cout << (pos == f.size() ? -1 : pos) << " ";
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
//    cin >> T;
    while (T--) {
        cin >> n >> C;
        for (int i = 1; i <= n; i++) {
            ll tc, td, th;
            cin >> tc >> td >> th;
            ll tw = td * th;
            c[i] = tc, w1[i] = tw;
        }
        cin >> m;
        for (int i = 1; i <= m; i++) {
            ll td, th;
            cin >> td >> th;
            ll tw = td * th;
            w2[i] = tw;
        }

        solve();
    }

    return 0;
}