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
using ai3 = array<int, 3>;

// region 无边权 scc
template<int N, class G>
struct Tarjan {
    int n;
    int dfn[N + 10], low[N + 10], ti;
    vector<int> stk;
    int ins[N + 10];
    int co[N + 10], sz[N + 10], scc;

    Tarjan() {}

    void init(int _n) {
        n = _n, ti = 0, scc = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }

    void tarjan(int u, const G &g) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u), ins[u] = 1;

        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];

            if (!dfn[v]) {
                tarjan(v, g);
                low[u] = min(low[u], low[v]);
            } else if (ins[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            scc++;
            int t;
            do {
                t = stk.back(); stk.pop_back(); ins[t] = 0;
                co[t] = scc;
                sz[scc]++;
            } while (t != u);
        }
    }

    // 有重边
    G suodian(const G &g) {
        G res;
        res.init(scc, -1);

        for (int u = 1; u <= n; u++) {
            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];
                if (co[u] == co[v]) continue;

                res.add(co[u], co[v]);
            }
        }

        return res;
    }
};
// endregion

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1010;

using G = Graph<2 * N, 4 * N * N>;

int n;
ai3 a[N];
G g;
Tarjan<2 * N, G> tj;

bool check(int l1, int r1, int l2, int r2) {
    return l2 < r1 && r2 > l1;
}

void init() {
    g.init(2 * n, -1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            auto [l1, r1, d1] = a[i];
            auto [l2, r2, d2] = a[j];

            if (check(l1, l1 + d1, l2, l2 + d2)) g.add(i, n + j), g.add(j, n + i);
            if (check(l1, l1 + d1, r2 - d2, r2)) g.add(i, j), g.add(n + j, n + i);
            if (check(r1 - d1, r1, l2, l2 + d2)) g.add(n + i, n + j), g.add(j, i);
            if (check(r1 - d1, r1, r2 - d2, r2)) g.add(n + i, j), g.add(n + j, i);
        }
    }
}

void solve() {
    init();

    tj.init(2 * n);
    for (int i = 1; i <= 2 * n; i++) {
        if (!tj.dfn[i]) tj.tarjan(i, g);
    }

    for (int i = 1; i <= n; i++) {
        if (tj.co[i] == tj.co[n + i]) {
            puts("NO");
            return;
        }
    }

    puts("YES");
    for (int i = 1; i <= n; i++) {
        auto [L, R, d] = a[i];

        if (tj.co[i] < tj.co[n + i]) printf("%02d:%02d %02d:%02d\n", L / 60, L % 60, (L + d) / 60, (L + d) % 60);
        else printf("%02d:%02d %02d:%02d\n", (R - d) / 60, (R - d) % 60, R / 60, R % 60);
    }
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
//    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int s0, s1, t0, t1, d;
            scanf("%d:%d %d:%d %d", &s0, &s1, &t0, &t1, &d);
            a[i] = {s0 * 60 + s1, t0 * 60 + t1, d};
        }

        solve();
    }

    return 0;
}