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

const int N = 5e4 + 10;

int n, m;
int ax[N], ay[N], ar[N];
int bx[N], by[N], br[N];

int nl;
vector<pii> lsh;
pii mp[2 * N];

int get(int x, int y) {
    return lower_bound(lsh.begin(), lsh.end(), (pii) {x, y}) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) {
        lsh.push_back({ax[i], ay[i]});
    }
    for (int i = 1; i <= m; i++) {
        lsh.push_back({bx[i], by[i]});
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) {
        int id = get(ax[i], ay[i]);
        mp[id].fi = max(mp[id].fi, ar[i]);
        mp[id].se++;
    }
    for (int i = 1; i <= m; i++) {
        int id = get(bx[i], by[i]);
        mp[id].fi = max(mp[id].fi, br[i]);
        mp[id].se++;
    }
}

ll calc(ll x1, ll y1, ll x2, ll y2) {
    ll dx = x1 - x2, dy = y1 - y2;
    ll d = dx * dx + dy * dy;
    return d;
}

void solve() {
    init();

    int ans = 0;
    queue<int> que;
    vector<int> vis(nl, 0);
    for (int i = 1; i <= m; i++) {
        int id = get(bx[i], by[i]);
        if (vis[id]) continue;
        que.push(id);
        vis[id] = 1;
        ans += mp[id].se;
    }
    while (!que.empty()) {
        auto u = que.front(); que.pop();
        auto [x, y] = lsh[u];
        int r = mp[u].fi;

        for (int dx = -r; dx <= r; dx++) {
            for (int dy = -r; dy <= r; dy++) {
                int nx = x + dx, ny = y + dy;
                int nid = get(nx, ny);
                if (nid < nl && lsh[nid].fi == nx && lsh[nid].se == ny) {
                    ll dis = calc(x, y, nx, ny);
                    if (!vis[nid] && dis <= r * r) {
                        que.push(nid);
                        vis[nid] = 1;
                        ans += mp[nid].se;
                    }
                }
            }
        }
    }

    ans -= m;
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
        for (int i = 1; i <= n; i++) cin >> ax[i] >> ay[i] >> ar[i];
        for (int i = 1; i <= m; i++) cin >> bx[i] >> by[i] >> br[i];
        solve();
    }

    return 0;
}