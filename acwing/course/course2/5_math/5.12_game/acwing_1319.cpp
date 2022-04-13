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

const int N = 2010;
const int M = 6010;

int n, m, k;
int a[N];
int h[N], ne[M], e[M], edm;
int sg[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int dfs(int u) {
    if (sg[u] != -1) return sg[u];

    set<int> st;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        int ret = dfs(v);

        st.insert(ret);
    }

    int res = 0;
    for (int i = 0; ; i++) {
        if (!st.count(i)) {
            res = i;
            break;
        }
    }

    return sg[u] = res;
}

void solve() {
    fill(sg, sg + n + 1, -1);

    int res = 0;
    for (int i = 1; i <= k; i++) {
        res ^= dfs(a[i]);
    }

    cout << (res != 0 ? "win" : "lose") << "\n";
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
        cin >> n >> m >> k;
        fill(h, h + n + 1, -1), edm = 0;
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v);
        }
        for (int i = 1; i <= k; i++) cin >> a[i];
        solve();
    }

    return 0;
}