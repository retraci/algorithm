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
const int N = 1010;

int n;
ai3 a[N];
Scc<2 * N, 4 * N * N> tj;

bool check(int l1, int r1, int l2, int r2) {
    return l2 < r1 && r2 > l1;
}

void init() {
    tj.init(2 * n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            auto [l1, r1, d1] = a[i];
            auto [l2, r2, d2] = a[j];

            if (check(l1, l1 + d1, l2, l2 + d2)) tj.add(tj.h1, i, n + j), tj.add(tj.h1, j, n + i);
            if (check(l1, l1 + d1, r2 - d2, r2)) tj.add(tj.h1, i, j), tj.add(tj.h1, n + j, n + i);
            if (check(r1 - d1, r1, l2, l2 + d2)) tj.add(tj.h1, n + i, n + j), tj.add(tj.h1, j, i);
            if (check(r1 - d1, r1, r2 - d2, r2)) tj.add(tj.h1, n + i, j), tj.add(tj.h1, n + j, i);
        }
    }
}

void solve() {
    init();

    for (int i = 1; i <= 2 * n; i++) {
        if (!tj.dfn[i]) tj.tarjan(i);
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