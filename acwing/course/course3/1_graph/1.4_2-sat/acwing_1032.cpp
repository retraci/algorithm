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
using ai4 = array<int, 4>;

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
const int N = 5e4 + 10;
const int M = 1e5 + 10;

int n, m, d;
string s;
ai4 a[M];
Scc<2 * N, 2 * M> tj;

int get(int u, int o, int f) {
    int c = s[u] - 'a';
    if (((c + 1) % 3 == o) ^ f) return u;
    else return n + u;
}

char put(int u, int t) {
    int c = s[u] - 'a';
    return 'A' + ((c + t) % 3);
}

void init() {
    tj.init(2 * n);

    for (int i = 1; i <= m; i++) {
        auto [u, o1, v, o2] = a[i];

        if (s[u] - 'a' != o1) {
            int u0 = get(u, o1, 0), u1 = get(u, o1, 1);
            int v0 = get(v, o2, 0), v1 = get(v, o2, 1);

            if (s[v] - 'a' != o2) {
                tj.add(tj.h1, u0, v0), tj.add(tj.h1, v1, u1);
            } else {
                tj.add(tj.h1, u0, u1);
            }
        }
    }
}

void work() {
    init();

    for (int i = 1; i <= 2 * n; i++) {
        if (!tj.dfn[i]) tj.tarjan(i);
    }

    for (int i = 1; i <= n; i++) {
        if (tj.co[i] == tj.co[n + i]) return;
    }

    for (int i = 1; i <= n; i++) {
        if (tj.co[i] < tj.co[n + i]) cout << put(i, 1);
        else cout << put(i, 2);
    }

    exit(0);
}

void solve() {
    for (int i = 1; i <= n; i++) s[i] = tolower(s[i]);
    vector<int> pos;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'x') pos.push_back(i);
    }

    int lim = 1 << d;
    for (int mask = 0; mask < lim; mask++) {
        for (int i = 0; i < pos.size(); i++) {
            if (mask >> i & 1) s[pos[i]] = 'a';
            else s[pos[i]] = 'b';
        }

        work();
    }

    cout << -1 << "\n";
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
        cin >> n >> d;
        cin >> s;
        s = ' ' + s;

        cin >> m;
        for (int i = 1; i <= m; i++) {
            int u, v;
            char o1, o2;
            cin >> u >> o1 >> v >> o2;
            o1 -= 'A', o2 -= 'A';
            a[i] = {u, o1, v, o2};
        }

        solve();
    }

    return 0;
}