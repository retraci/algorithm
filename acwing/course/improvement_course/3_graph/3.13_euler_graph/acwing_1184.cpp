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
const int M = 2e5 + 10;

int type, n, m;
int g[M * 2], ne[M * 2], h[N], edm;
int din[N], dout[N];

vector<int> ans;
int vis[2 * M];

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u) {
    while (~h[u]) {
        int eid = h[u]; h[u] = ne[eid];
        if (vis[eid]) continue;

        auto v = g[eid];
        if (type == 1) vis[eid] = vis[eid ^ 1] = 1;
        dfs(v);

        int t;
        if (type == 1) {
            t = eid / 2 + 1;
            if (eid & 1) t = -t;
        } else {
            t = eid + 1;
        }
        ans.push_back(t);
    }
}

void solve() {
    if (type == 1) {
        for (int i = 1; i <= n; i++) {
            if (din[i] + dout[i] & 1) {
                cout << "NO" << "\n";
                return;
            }
        }
    } else {
        for (int i = 1; i <= n; i++) {
            if (din[i] != dout[i]) {
                cout << "NO" << "\n";
                return;
            }
        }
    }

    int st = 0;
    for (int i = 1; i <= n; i++) {
        if (~h[i]) {
            st = i;
            break;
        }
    }
    if (st > 0) dfs(st);

    if (ans.size() < m) {
        cout << "NO" << "\n";
        return;
    }

    cout << "YES" << "\n";
    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << " ";
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
        cin >> type >> n >> m;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v);
            if (type == 1) add(v, u);
            din[v]++, dout[u]++;
        }

        solve();
    }

    return 0;
}