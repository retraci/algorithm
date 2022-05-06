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

// region scc 无权缩点
template<int N, int M>
struct Scc {
    int n;
    int h1[N + 10], h2[N + 10], ne[2 * M + 10], e[2 * M + 10], edm;
    int dfn[N], low[N], ti;
    vector<int> stk;
    int ins[N];
    int co[N], sz[N], scc;

    Scc() {}

    void init(int _n) {
        n = _n, ti = 0, scc = 0;
        fill(h1, h1 + n + 1, -1), edm = 0;
        fill(dfn, dfn + n + 1, 0);
        fill(sz, sz + n + 1, 0);
    }

    void add(int h[], int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++ti;
        stk.push_back(u), ins[u] = 1;

        for (int i = h1[u]; ~i; i = ne[i]) {
            int v = e[i];

            if (!dfn[v]) {
                tarjan(v);
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

    void suodian() {
        fill(h2, h2 + scc + 1, -1);

        for (int u = 1; u <= n; u++) {
            for (int i = h1[u]; ~i; i = ne[i]) {
                int v = e[i];
                if (co[u] == co[v]) continue;

                add(h2, co[u], co[v]);
            }
        }
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;
const int M = 1e6 + 10;

int n, m;
Scc<2 * N, 2 * M> tj;

void solve() {
    for (int i = 1; i <= n * 2; i++) {
        if (!tj.dfn[i]) tj.tarjan(i);
    }

    for (int i = 1; i <= n; i++) {
        if (tj.co[i] == tj.co[i + n]) {
            cout << "IMPOSSIBLE" << "\n";
            return;
        }
    }

    cout << "POSSIBLE" << "\n";
    for (int i = 1; i <= n; i++) {
        if (tj.co[i] < tj.co[i + n]) cout << 0 << " ";
        else cout << 1 << " ";
    }
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m;
        tj.init(2 * n);

        for (int k = 1; k <= m; k++) {
            int i, a, j, b;
            cin >> i >> a >> j >> b;
            int u0 = a ? i : n + i, u1 = a ? n + i : i;
            int v0 = b ? j : n + j, v1 = b ? n + j : j;

            tj.add(tj.h1, u0, v1);
            tj.add(tj.h1, v0, u1);
        }

        solve();
    }

    return 0;
}