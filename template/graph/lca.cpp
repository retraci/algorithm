#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

/*----------------------------------------*/

typedef pair<int, int> pii;

int n, m;
vector<pii> g[N];
int fa[N][31], cost[N][31], dep[N];

// 有边权的
// dfs, 用来为 lca 算法做准备, 接受两个参数: dfs 起始节点和它的父亲节点
void dfs_lca(int u, int fno) {
    // 初始化: 第 2^0 = 1 个祖先就是它的父亲节点, dep 也比父亲节点多 1
    fa[u][0] = fno;
    dep[u] = dep[fa[u][0]] + 1;
    // 初始化: 其他的祖先节点: 第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点
    for (int i = 1; i < 31; i++) {
        int pv = fa[u][i - 1];
        fa[u][i] = fa[pv][i - 1];
        cost[u][i] = cost[pv][i - 1] + cost[u][i - 1];
    }
    // 遍历子节点来进行 dfs
    for (auto &[v, w] : g[u]) {
        if (v == fno) continue;
        cost[v][0] = w[u][i];
        dfs_lca(v, u);
    }
}

// lca, 用倍增算法算取 x 和 y 的 lca 节点
// 可以返回2种答案: 1.返回 ans, x 与 y 的路径和; 2.返回 fa[x][0], 则返回 lca(x, y)
int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    // y 向上爬
    int delta = dep[y] - dep[x], res = 0;
    for (int i = 0; delta; i++, delta >>= 1) {
        if (delta & 1) y = fa[y][i], res += cost[y][i];
    }
    // 如果这个时候 y = x, 那么 x, y 就都是它们自己的祖先
    if (y == x) return res;

    // 不然的话, 找到第一个不是它们祖先的两个点
    for (int i = 30; i >= 0 && y != x; i--) {
        if (fa[x][i] != fa[y][i]) {
            res += cost[x][i] + cost[y][i];
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    // 再向上爬一层就是 lca 了
    res += cost[x][0] + cost[y][0];
    return res;
}