// region 普通floyd
// 初始 (1 - n)
int f[N][N];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
}
// endregion

// region 传递闭包 floyd
// bitset 优化(1 - n)
bitset<N> f[N];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (f[i][k]) f[i] |= f[k];
        }
    }
}
// endregion

// region 无向图最小环 (1 - n) floyd
void dfs(int i, int j) {
    if (pre[i][j] == 0) return;

    int k = pre[i][j];
    dfs(i, k);
    path.push_back(k);
    dfs(k, j);
}

void floyd() {
    mi = 1e9;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (mi > 1LL * g[k][i] + f[i][j] + g[j][k]) {
                    mi = g[k][i] + f[i][j] + g[j][k];

                    path.clear();
                    path.push_back(k);
                    path.push_back(i);
                    dfs(i, j);
                    path.push_back(j);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (f[i][j] > f[i][k] + f[k][j]) {
                    f[i][j] = f[i][k] + f[k][j];
                    pre[i][j] = k;
                }
            }
        }
    }
}
// endregion

// region 强制走 K 个边 floyd
void work(int u[][N], int v[][N]) {
    int res[N][N];
    memset(res, 0x3f, sizeof res);

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                res[i][j] = min(res[i][j], u[i][k] + v[k][j]);
            }
        }
    }

    memcpy(u, res, sizeof res);
}

void ksm() {
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; i++) f[i][i] = 0;

    // g 仅为走 1 次的状态, 走 0 次的状态不应该存在在 g 里
    while (K) {
        if (K & 1) work(f, g);
        work(g, g);
        K >>= 1;
    }
}
// endregion
