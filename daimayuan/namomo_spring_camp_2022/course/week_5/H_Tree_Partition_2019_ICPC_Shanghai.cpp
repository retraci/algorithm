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

int n, m, ca;
int a[N];

int h[N], ne[2 * N], g[2 * N], edm;

ll f1[N], f2[N];

void add(int u, int v){
    g[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno, ll lim) {
    f1[u] = 0, f2[u] = a[u];
    if (a[u] > lim) f1[u] = 1e9;

    vector<ll> b;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;

        dfs(v, u, lim);

        f1[u] += f1[v];
        b.push_back(f2[v]);
    }

    sort(b.begin(), b.end());
    for (ll x : b) {
        if (f2[u] + x <= lim) f2[u] += x;
        else f1[u]++;
    }
}

bool check(ll mid) {
    dfs(1, 0, mid);
    return f1[1] + 1 <= m;
}

void solve() {
    ll left = 0, right = 1e18;
    while (left < right) {
        ll mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    char out[111];
    snprintf(out, 111, "Case #%d: %lld", ++ca, left);
    cout << string(out) << "\n";
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        for (int i = 1; i <= n; i++) cin >> a[i];

        solve();
    }

    return 0;
}