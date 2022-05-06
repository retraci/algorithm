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
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;

// region edmonds
template<int N, int M>
struct Edmonds {
    using Edge = tuple<int, int, double>;

    const double INF = 1e18;
    int n, m;
    Edge es[M + 10];
    double in[N + 10];
    int vis[N + 10], co[N + 10], pre[N + 10];

    Edmonds() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
    }

    double work(int rt) {
        double res = 0;

        while (1) {
            fill(in, in + n + 1, INF);

            for (int i = 1; i <= m; i++) {
                auto [u, v, cost] = es[i];

                if (in[v] > cost) {
                    in[v] = cost, pre[v] = u;
                }
            }

            for (int i = 1; i <= n; i++) {
                if (in[i] == INF && i != rt) return -1;
            }

            fill(vis, vis + n + 1, 0);
            fill(co, co + n + 1, 0);
            int cnt = 0;
            for (int i = 1; i <= n; i++) {
                if (i == rt) continue;

                res += in[i];
                int v = i;
                while (v != rt && !co[v] && vis[v] != i) vis[v] = i, v = pre[v];
                if (v != rt && vis[v] == i) {
                    co[v] = ++cnt;
                    for (int t = pre[v]; t != v; t = pre[t]) co[t] = cnt;
                }
            }
            if (cnt == 0) break;

            for (int i = 1; i <= n; i++) {
                if (!co[i]) co[i] = ++cnt;
            }
            int tt = 0;
            for (int i = 1; i <= m; i++) {
                auto [u, v, cost] = es[i];
                if (co[u] == co[v]) continue;

                es[++tt] = {co[u], co[v], cost - in[v]};
            }

            n = cnt, m = tt, rt = co[rt];
        }

        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 110;
const int M = 1e4 + 10;

int n, m;
pii a[N];
pii es[M];
Edmonds<N, M> ed;

double get(int x1, int y1, int x2, int y2) {
    ll dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

void init() {
    for (int i = 1; i <= m; i++) {
        auto[u, v] = es[i];
        double cost = get(a[u].fi, a[u].se, a[v].fi, a[v].se);
        ed.es[i] = {u, v, cost};
    }
}

void solve() {
    init();

    ed.init(n, m);
    double ans = ed.work(1);
    if (ans == -1) {
        cout << "poor snoopy" << "\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << ans << "\n";
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
    int _ = 1;
//    cin >> _;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        for (int i = 1; i <= m; i++) cin >> es[i].fi >> es[i].se;
        solve();
    }

    return 0;
}