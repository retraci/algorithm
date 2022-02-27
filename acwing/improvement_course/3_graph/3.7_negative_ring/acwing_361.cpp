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

const int N = 1010;
const int M = 5010;
const double eps = 1e-4;

int n, m;
int a[N];
pii g[M];
int ne[M], h[N], edm;

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

bool check(double mid) {
    vector<int> st(n + 1, 0), cnt(n + 1, 0);
    vector<double> dist(n + 1, 0);

    deque<int> que;
    for (int i = 1; i <= n; i++) que.push_back(i), st[i] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop_front();
        st[u] = 0;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v] > dist[u] + -(a[v] - cost * mid)) {
                dist[v] = dist[u] + -(a[v] - cost * mid);
                cnt[v] = cnt[u] + 1;

                if (cnt[v] >= n) return true;
                if (!st[v]) {
                    st[v] = 1;
                    if (!que.empty() && dist[v] < dist[que.front()]) que.push_front(v);
                    else que.push_back(v);
                }
            }
        }
    }

    return false;
}

void solve() {
    double left = 0, right = 1000;
    while (left + eps < right) {
        double mid = (left + right) / 2;
        if (check(mid)) left = mid;
        else right = mid;
    }

    cout << fixed << setprecision(2);
    cout << left << "\n";
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

        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            add(u, v, cost);
        }
        solve();
    }

    return 0;
}