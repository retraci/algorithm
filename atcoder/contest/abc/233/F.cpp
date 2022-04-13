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

const int N = 1e3 + 10;
const int M = 2e5 + 10;

int n, m;
int a[N];
pii b[M];

int h[N], ne[2 * M], edm;
pii e[2 * M];
int du[N];

int pa[N];
vector<int> ans;

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

bool unite(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return false;
    pa[tx] = ty;
    return true;
}

void add(int u, int v, int eid) {
    e[edm] = {v, eid}; ne[edm] = h[u], h[u] = edm++;
}

bool dfs(int u, int fno, int tar) {
    if (u == tar) return 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        auto [v, eid] = e[i];
        if (v == fno) continue;

        if (dfs(v, u, tar)) {
            swap(a[u], a[v]);
            ans.push_back(eid);
            return 1;
        }
    }

    return 0;
}

void init() {
    fill(h, h + n + 1, -1), edm = 0;
    iota(pa, pa + n + 1, 0);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = b[i];

        if (unite(u, v)) {
            add(u, v, i), add(v, u, i);
            du[u]++, du[v]++;
        }
    }
}

void solve() {
    init();

    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (du[i] == 1) que.push(i);
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();

        int tar = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] == u) tar = i;
        }
        if (!dfs(u, 0, tar)) {
            cout << -1 << "\n";
            return;
        }

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, eid] = e[i];
            if (--du[v] == 1) que.push(v);
        }
    }

    cout << ans.size() << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            b[i] = {u, v};
        }
        solve();
    }

    return 0;
}