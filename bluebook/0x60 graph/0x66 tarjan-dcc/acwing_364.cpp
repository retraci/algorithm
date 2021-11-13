#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

const int N = 100010;

typedef pair<int, int> pii;

int T;
int n, m;
vector<int> g[N];
int dfn[N], low[N], num;
unordered_set<int> bridge[N];

int dcc, c[N];
vector<int> gc[N];

int f[N][31], cost[N][31], dep[N];
int fa[N];

void init() {
    for (int i = 1; i <= n; i++) g[i] = {};
    for (int i = 1; i <= n; i++) dfn[i] = 0;
    num = 0;
    for (int i = 1; i <= n; i++) bridge[i] = {};

    dcc = 0;
    for (int i = 1; i <= n; i++) c[i] = 0;
    for (int i = 1; i <= n; i++) gc[i] = {};
    for (int i = 1; i <= n; i++) fa[i] = i;
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void add_c(int u, int v) {
    gc[u].push_back(v);
}

void dfs_suodian(int u) {
    c[u] = dcc;
    for (int v : g[u]) {
        if (c[v] || bridge[u].count(v)) continue;
        dfs_suodian(v);
    }
}

void suodian() {
    dcc = 0;
    for (int i = 1; i <= n; i++) {
        if (!c[i]) {
            ++dcc;
            dfs_suodian(i);
        }
    }

    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (c[u] == c[v]) continue;
            add_c(c[u], c[v]), add_c(c[v], c[u]);
        }
    }
}

// 割边
void tarjan(int u, int pa) {
    dfn[u] = low[u] = ++num;
    for (int v : g[u]) {
        // 没走过
        if (!dfn[v]) {
            tarjan(v, u);
            // 把孩子的 low 更新到自己
            low[u] = min(low[u], low[v]);

            // 发现割边 u -> v
            if (low[v] > dfn[u]) {
                bridge[u].insert(v);
                bridge[v].insert(u);
            }
        } else if (v != pa) {
            // 遇到走过的, 就把走过的 dfn 更新一下
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 有边权的
// dfs, 用来为 lca 算法做准备, 接受两个参数: dfs 起始节点和它的父亲节点
void dfs_lca(int u, int fno) {
    // 初始化: 第 2^0 = 1 个祖先就是它的父亲节点, dep 也比父亲节点多 1
    f[u][0] = fno;
    dep[u] = dep[f[u][0]] + 1;
    // 初始化: 其他的祖先节点: 第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点
    for (int i = 1; i < 31; i++) {
        int pv = f[u][i - 1];
        f[u][i] = f[pv][i - 1];
        cost[u][i] = cost[pv][i - 1] + cost[u][i - 1];
    }
    // 遍历子节点来进行 dfs
    for (int v : gc[u]) {
        if (v == fno) continue;
        cost[v][0] = 1;
        dfs_lca(v, u);
    }
}

// lca, 用倍增算法算取 x 和 y 的 lca 节点
// 可以返回2种答案: 1.返回 ans, x 与 y 的路径和; 2.返回 f[x][0], 则返回 lca(x, y)
int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    // y 向上爬
    int delta = dep[y] - dep[x], res = 0;
    for (int i = 0; delta; i++, delta >>= 1) {
        if (delta & 1) y = f[y][i], res += cost[y][i];
    }
    // 如果这个时候 y = x, 那么 x, y 就都是它们自己的祖先
    if (y == x) return x;

    // 不然的话, 找到第一个不是它们祖先的两个点
    for (int i = 30; i >= 0 && y != x; i--) {
        if (f[x][i] != f[y][i]) {
            res += cost[x][i] + cost[y][i];
            x = f[x][i];
            y = f[y][i];
        }
    }
    // 再向上爬一层就是 lca 了
    res += cost[x][0] + cost[y][0];
    return f[x][0];
}

void add(int u, int v) {
    g[u].push_back(v);
}

void solve() {
    cout << "Case " + to_string(++T) + ":" << endl;

    tarjan(1, 0), suodian();
    dfs_lca(1, 0);

    int cur = dcc - 1;
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x = find(c[x]), y = find(c[y]);

        int tar = lca(x, y);

        while (dep[x] > dep[tar]) {
            fa[x] = f[x][0];
            cur--;
            x = find(x);
        }
        while (dep[y] > dep[tar]) {
            fa[y] = f[y][0];
            cur--;
            y = find(y);
        }
        cout << cur << endl;
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n >> m, n) {
        init();
        while (m--) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}