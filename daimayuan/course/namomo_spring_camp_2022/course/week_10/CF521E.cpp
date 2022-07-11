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

const int N = 2e5 + 10;

int n, m;
int h[N], ne[2 * N], e[2 * N], edm;
int fa[N], dep[N], vis[N], ins[N];
int cnt[N], vs[N], vt[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int lca(int x, int y) {
    if (dep[x] != dep[y]) {
        if (dep[x] > dep[y]) swap(x, y);
        while (dep[y] > dep[x]) y = fa[y];
    }
    if (x == y) return x;
    while (x != y) x = fa[x], y = fa[y];
    return x;
}

void work(int a, int b, int c, int d) {
    cout << "YES" << "\n";

    if (dep[a] > dep[c]) swap(a, c), swap(b, d);
    int f = lca(b, d);

    {
        stack<int> stk;
        int t = f;
        while (t != c) stk.push(t), t = fa[t];
        stk.push(t);
        cout << stk.size() << " ";
        while (!stk.empty()) cout << stk.top() << " ", stk.pop();
        cout << "\n";
    }

    {
        int sz = dep[c] - dep[a] + dep[b] - dep[f] + 2;
        cout << sz << " ";
        int t = c;
        while (t != a) cout << t << " ", t = fa[t];
        cout << t << " ";

        t = b;
        while (t != f) cout << t << " ", t = fa[t];
        cout << t << " ";
        cout << "\n";
    }

    {
        int sz = dep[d] - dep[f] + 2;
        cout << sz << " ";
        cout << c << " ";
        int t = d;
        while (t != f) cout << t << " ", t = fa[t];
        cout << t << " ";
        cout << "\n";
    }

    exit(0);
}

void dfs(int u, int fno) {
    vis[u] = 1, ins[u] = 1;
    dep[u] = dep[fno] + 1, fa[u] = fno;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        if (!vis[v]) {
            dfs(v, u);
        } else if (ins[v]) {
            int t = u;
            while (t != v) {
                if (++cnt[t] >= 2) work(vt[t], vs[t], v, u);
                vs[t] = u, vt[t] = v;

                t = fa[t];
            }
        }
    }

    ins[u] = 0;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i, 0);
    }

    cout << "NO" << "\n";
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}