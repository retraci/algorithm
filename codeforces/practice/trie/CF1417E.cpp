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

int n;
int a[N];

int tr[31 * N][2], mem;
vector<int> b[31 * N];
ll f[33][2];

void add(int x, int pos) {
    int u = 0;
    for (int i = 30; i >= 0; i--) {
        int bi = x >> i & 1;
        if (!tr[u][bi]) tr[u][bi] = ++mem;
        u = tr[u][bi];
        b[u].push_back(pos);
    }
}

void dfs(int u, int lev) {
    int ls = tr[u][0], rs = tr[u][1];
    if (!ls && !rs) return;

    ll id = 0, c1 = 0;
    for (int x : b[ls]) {
        while (id < b[rs].size() && x > b[rs][id]) id++;
        c1 += id;
    }
    ll c2 = 1LL * b[ls].size() * b[rs].size() - c1;

    f[lev][0] += c1, f[lev][1] += c2;

    if (ls) dfs(ls, lev - 1);
    if (rs) dfs(rs, lev - 1);
}

void solve() {
    for (int i = 1; i <= n; i++) add(a[i], i);

    dfs(0, 30);

    ll ans = 0, cnt = 0;
    for (int i = 0; i <= 30; i++) {
        if (f[i][1] < f[i][0]) ans |= 1 << i;
        cnt += min(f[i][0], f[i][1]);
    }

    cout << cnt << " " << ans << "\n";
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