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

const int N = 2e3 + 10;
const int M = 1e4 + 10;

int n, m;
int a[N];
pii es[M];
int h[N], ne[M], e[M], edm;
int deg[N], tag[N], vis[N];
vector<int> c[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

int dfs(int u) {
    if (vis[u]) return a[u];
    vis[u] = 1;

    int res = min(n, a[u]);
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];

        int ret = dfs(v);
        res = min(res, ret - 1);
    }

    c[res].push_back(u);
    return a[u] = res;
}

void dfs2(int u) {
    if (tag[u]) return;

    tag[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];

        dfs2(v);
    }
}

void solve() {
    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        add(u, v), deg[v]++;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) dfs(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int x : c[i]) cout << x << " ";
    }
    cout << "\n";

    fill(h, h + n + 1, -1), edm = 0;
    for (int i = 1; i <= m; i++) {
        auto [u, v] = es[i];
        add(v, u);
    }

    for (int i = 1; i <= n; i++) {
        fill(tag, tag + n + 1, 0);
        dfs2(i);

        int cur = n;
        for (int j = n; j >= 1; j--) {
            if (cur > j) break;

            for (int k : c[j]) {
                cur -= !tag[k];
            }
        }
        cout << cur << " ";
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            es[i] = {u, v};
        }
        solve();
    }

    return 0;
}