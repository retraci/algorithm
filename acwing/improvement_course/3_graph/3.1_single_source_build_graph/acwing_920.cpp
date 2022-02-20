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
const int M = N * N;

int n, m;
pii g[M * 2];
int ne[M * 2], h[N], edm;

void add(int u, int v, int cost) {
    g[edm] = {v, cost};
    ne[edm] = h[u], h[u] = edm++;
}

int bfs() {
    int dist[n + 1];
    memset(dist, -1, sizeof dist);

    queue<int> que;
    que.push(1);
    dist[1] = 0;
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cost] = g[i];

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }

    return dist[n];
}

void solve() {
    int ret = bfs();
    if (ret == -1) cout << "NO" << "\n";
    else cout << max(ret - 1, 0) << "\n";
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
        cin >> m >> n;
        memset(h, -1, sizeof h);

        string str;
        getline(cin, str);
        for (int i = 1; i <= m; i++) {
            getline(cin, str);
            stringstream ss(str);

            int va[n + 1], cnt = 0;
            while (ss >> va[cnt]) cnt++;
            for (int j = 0; j < cnt; j++) {
                for (int k = j + 1; k < cnt; k++) {
                    add(va[j], va[k], 1);
                }
            }
        }
        solve();
    }

    return 0;
}