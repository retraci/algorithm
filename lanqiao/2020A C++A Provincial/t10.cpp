#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 10010;
const int M = 1e5 + 10;

int n, m;
int op[M], va[M], vb[M];
int fa[M + N], d[M + N];

int find(int x) {
    // 根节点的孩子不压缩 (!important)
    if (x == fa[x] || fa[x] == fa[fa[x]]) return fa[x];
    int rt = find(fa[x]);
    d[x] += d[fa[x]];
    return fa[x] = rt;
}

void solve() {
    for (int i = 1; i < M; i++) fa[i] = i;
    memset(d, 0, sizeof d);

    int tot = n;
    for (int i = 0; i < m; i++) {
        int o = op[i], a = va[i], b = vb[i];
        if (o == 1) {
            int tx = find(a), ty = find(b);
            if (tx == ty) continue;
            fa[tx] = fa[ty] = ++tot;
        } else {
            int tx = find(a);
            d[tx] += b;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i == find(i)) printf("%d ", d[i]);
        else printf("%d ", d[i] + d[find(i)]);
    }
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &op[i], &va[i], &vb[i]);
    }
    solve();

    return 0;
}