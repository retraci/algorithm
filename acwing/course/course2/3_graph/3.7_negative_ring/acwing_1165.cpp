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

const int N = 26 * 26;
const int M = 1e5 + 10;
const double eps = 1e-4;

int m;
string a[M];
pii g[M];
int ne[M], h[N], edm;

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void init() {
    memset(h, -1, sizeof h), edm = 0;

    for (int i = 1; i <= m; i++) {
        int sz = a[i].size();
        if (sz < 2) continue;
        int u = (a[i][0] - 'a') * 26 + (a[i][1] - 'a'), v = (a[i][sz - 2] - 'a') * 26 + (a[i][sz - 1] - 'a');
        add(u, v, sz);
    }
}

bool check(double mid) {
    vector<int> st(N, 0), cnt(N, 0);
    vector<double> dist(N, 0);

    deque<int> que;
    for (int i = 0; i < N; i++) que.push_back(i), st[i] = 1;
    while (!que.empty()) {
        auto u = que.front(); que.pop_front();
        st[u] = 0;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v] > dist[u] + -(cost - mid)) {
                dist[v] = dist[u] + -(cost - mid);
                cnt[v] = cnt[u] + 1;

                if (cnt[v] >= N) return true;
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
    init();

    double left = 0, right = 1000;
    while (left + eps < right) {
        double mid = (left + right) / 2;
        if (check(mid)) left = mid;
        else right = mid;
    }

    if (left < eps) {
        cout << "No solution" << "\n";
        return;
    }
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
    while (cin >> m, m) {
        for (int i = 1; i <= m; i++) cin >> a[i];
        solve();
    }

    return 0;
}