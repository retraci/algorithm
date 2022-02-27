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

const int N = 30;
const int M = 100;

int a[N], r[N];

int m;
pii g[M];
int ne[M], h[N], edm;

void add(int u, int v, int cost) {
    g[edm] = {cost, v};
    ne[edm] = h[u], h[u] = edm++;
}

void init(int c) {
    memset(h, -1, sizeof h), edm = 0;

    for (int i = 1; i <= 24; i++) {
        if (i - 8 >= 0) add(i - 8, i, r[i]);
        else add(i + 16, i, r[i] - c);
    }

    for (int i = 1; i <= 24; i++) {
        add(i - 1, i, 0);
        add(i, i - 1, -a[i]);
    }

    add(0, 24, c), add(24, 0, -c);
}

bool spfa() {
    vector<int> dist(25, -1e9), st(25, 0), cnt(25, 0);
    deque<int> que;
    for (int i = 0; i <= 24; i++) {
        dist[i] = 0;
        que.push_back(i), st[i] = 1;
    }

    while (!que.empty()) {
        auto u = que.front(); que.pop_front();
        st[u] = 0;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [cost, v] = g[i];

            if (dist[v] < dist[u] + cost) {
                dist[v] = dist[u] + cost;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= 25) return false;

                if (!st[v]) {
                    st[v] = 1;
                    if (!que.empty() && dist[v] > dist[que.front()]) que.push_front(v);
                    else que.push_back(v);
                }
            }
        }
    }

    return true;
}

void solve() {
    int flag = 0;
    for (int i = 0; i <= m; i++) {
        init(i);

        if (spfa()) {
            cout << i << "\n";
            flag = 1;
            break;
        }
    }

    if (!flag) cout << "No Solution" << "\n";
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
        for (int i = 1; i <= 24; i++) cin >> r[i];

        memset(a, 0, sizeof a);
        m = 0;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int t;
            cin >> t;
            t++;
            a[t]++;
        }

        solve();
    }

    return 0;
}