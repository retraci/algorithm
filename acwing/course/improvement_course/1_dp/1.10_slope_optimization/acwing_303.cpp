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

const int P = 110;
const int N = 1e5 + 10;

int n, m, p;
ll d[N], h[N], t[N];
ll a[N], s[N];

ll f[P][N];
int que[N], hh, tt;

void init() {
    for (int i = 1; i <= n; i++) d[i] += d[i - 1];
    for (int i = 1; i <= m; i++) a[i] = t[i] - d[h[i]];

    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) s[i] = s[i - 1] + a[i];
}

ll get_y(int i, int k) {
    return f[i][k] + s[k];
}

void solve() {
    init();

    memset(f, 0x3f, sizeof f);
    for (int i = 0; i <= p; i++) f[i][0] = 0;
    for (int i = 1; i <= p; i++) {
        hh = 0, tt = 0;
        que[0] = 0;
        for (int j = 1; j <= m; j++) {
            while (tt > hh) {
                ll x1 = que[hh], x2 = que[hh + 1];
                ll y1 = get_y(i - 1, que[hh]), y2 = get_y(i - 1, que[hh + 1]);
                if (a[j] * (x2 - x1) < (y2 - y1)) break;
                hh++;
            }

            int k = que[hh];
            f[i][j] = f[i - 1][k] - a[j] * k + s[k] + a[j] * j - s[j];

            while (tt > hh) {
                ll x1 = que[tt - 1], x2 = que[tt];
                ll y1 = get_y(i - 1, que[tt - 1]), y2 = get_y(i - 1, que[tt]);
                ll x = j, y = get_y(i - 1, j);
                if ((y - y2) * (x2 - x1) > (y2 - y1) * (x - x2)) break;
                tt--;
            }
            que[++tt] = j;
        }
    }

    cout << f[p][m] << "\n";
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
        cin >> n >> m >> p;
        for (int i = 2; i <= n; i++) cin >> d[i];
        for (int i = 1; i <= m; i++) cin >> h[i] >> t[i];
        solve();
    }

    return 0;
}