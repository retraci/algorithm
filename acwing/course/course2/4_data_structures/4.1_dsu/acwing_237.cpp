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

int n;
deque<ti3> a;
vector<int> lsh;

int fa[N * 2];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void solve() {
    lsh.clear();
    for (auto [t, u, v] : a) {
        lsh.push_back(u), lsh.push_back(v);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());

    iota(fa, fa + lsh.size(), 0);
    int cur = 0;
    while (cur < n) {
        auto [t, u, v] = a[cur];
        if (t == 0) break;

        u = get(u), v = get(v);
        unite(u, v);
        cur++;
    }

    int flag = 0;
    while (cur < n) {
        auto [t, u, v] = a[cur];
        u = get(u), v = get(v);

        int tu = find(u), tv = find(v);
        if (tu == tv) flag = 1;
        cur++;
    }

    cout << (flag ? "NO" : "YES") << "\n";
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
        a.clear();
        for (int i = 1; i <= n; i++) {
            int u, v, t;
            cin >> u >> v >> t;
            if (t) a.push_front({t, u, v});
            else a.push_back({t, u, v});
        }

        solve();
    }

    return 0;
}