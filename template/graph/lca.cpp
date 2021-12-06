#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

/*----------------------------------------*/

typedef pair<int, int> pii;

vector<pii> g[N];
int fa[N][31], cost[N][31], dep[N];

// 有边权的
// dfs, 用来为 lca 算法做准备, 接受两个参数: dfs 起始节点和它的父亲节点
void dfs_lca(int u, int fno) {
    fa[u][0] = fno, dep[u] = dep[fno] + 1;

    for (int i = 1; i < 31; i++) {
        int pv = fa[u][i - 1];
        fa[u][i] = fa[pv][i - 1];
        cost[u][i] = cost[pv][i - 1] + cost[u][i - 1];
    }

    for (auto &[v, w] : g[u]) {
        if (v == fno) continue;
        cost[v][0] = w;
        dfs_lca(v, u);
    }
}

// lca, 用倍增算法算取 x 和 y 的 lca 节点
// 可以返回2种答案:
// 1.返回 ans, x 与 y 的路径和;
// 2.返回 fa[x][0], 则返回 lca(x, y)
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);

    int delta = dep[x] - dep[y], res = 0;
    for (int i = 0; delta; i++, delta >>= 1) {
        if (delta & 1) x = fa[x][i], res += cost[x][i];
    }
    if (x == y) return x;

    for (int i = 30; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            res += cost[x][i] + cost[y][i];
            x = fa[x][i], y = fa[y][i];
        }
    }

    res += cost[x][0] + cost[y][0];
    return fa[x][0];
}