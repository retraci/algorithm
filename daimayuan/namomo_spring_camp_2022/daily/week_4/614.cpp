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

const int N = 3e3 + 10;

int n, m;
string g[N];
int ls[N][N], rs[N][N];

pii a[N];
int tt;
vector<int> del[N];
int tr[N];

void upd(int id, int x) {
    for (int i = id; i <= tt; i += i & -i) tr[i] += x;
}

int qr(int id) {
    int res = 0;
    for (int i = id; i; i -= i & -i) res += tr[i];
    return res;
}

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'z') ls[i][j] = ls[i][j - 1] + 1;
        }
        for (int j = m; j >= 1; j--) {
            if (g[i][j] == 'z') rs[i][j] = rs[i][j + 1] + 1;
        }
    }
}

int work() {
    int res = 0;

    for (int i = 1; i <= tt; i++) tr[i] = 0, del[i].clear();
    for (int i = 1; i <= tt; i++) {
        auto [L, R] = a[i];
        upd(i, 1);

        int lb = max(1, i - R + 1);
        res += qr(i) - qr(lb - 1);

        del[min(tt, i + L - 1)].push_back(i);
        for (int x : del[i]) upd(x, -1);
    }

    return res;
}

void solve() {
    init();

    ll ans = 0;
    for (int d = 2; d <= n + m; d++) {
        for (int i = max(1, d - m); i <= min(n, d - 1); i++) {
            int j = d - i;
            if (g[i][j] != 'z') {
                if (tt) {
                    ans += work();
                    tt = 0;
                }
            } else {
                a[++tt] = {ls[i][j], rs[i][j]};
            }
        }
        if (tt) {
            ans += work();
            tt = 0;
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
//    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}