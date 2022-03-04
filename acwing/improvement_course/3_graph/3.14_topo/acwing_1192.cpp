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

const int N = 10010;
const int M = 20010;

int n, m;
int g[M], ne[M], h[N], edm;
int in[N];

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void solve() {
    vector<int> ans(n + 1, -1);
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            ans[i] = 100;
            que.push(i);
        }
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = g[i];

            if (--in[v] == 0) {
                que.push(v);
                ans[v] = max(ans[v], ans[u] + 1);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == -1) {
            cout << "Poor Xed" << "\n";
            return;
        }
    }

    cout << accumulate(ans.begin() + 1, ans.end(), 0LL) << "\n";
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
        fill(h, h + n + 1, -1), edm = 0;
        fill(in, in + n + 1, 0);

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(v, u), in[u]++;
        }

        solve();
    }

    return 0;
}