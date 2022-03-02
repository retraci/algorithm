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

const int N = 510;

int n, m;
vector<int> g[N];
int du[N];

int vis[N][N];
vector<int> ans;

void add(int u, int v) {
    g[u].push_back(v);
}

void dfs(int u) {
    while (!g[u].empty()) {
        int v = g[u].back(); g[u].pop_back();
        if (vis[u][v] == 0) continue;
        vis[u][v]--, vis[v][u]--;
        dfs(v);
    }
    ans.push_back(u);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end(), greater<>());
    }

    int st = 1;
    for (int i = 1; i <= n; i++) {
        if (du[i] & 1) {
            st = i;
            break;
        }
    }
    dfs(st);

    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << "\n";
}

void prework() {
    n = 500;
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
        cin >> m;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
            vis[u][v]++, vis[v][u]++;
            du[u]++, du[v]++;
        }
        solve();
    }

    return 0;
}