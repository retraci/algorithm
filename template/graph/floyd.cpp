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

// region 传递闭包

// bitset 优化(1 - n)
bitset <N> f[N];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (f[i][k]) f[i] = f[i] | f[k];
        }
    }
}
// endregion

// region 最小环 (1 - n)

// pos[i][j] 表示 i 到 j 经过了 k
int f[N][N];
int pos[N][N];
vector<int> path;

// i->j之间的路, 输出i到j之间不包括i和j的道路
void dfs(int i, int j) {
    int k = pos[i][j];
    // 如果是0, 说明i, j之间不经过除i, j之外的其他点
    if (k == 0) return;

    dfs(i, k);
    path.push_back(k);
    dfs(k, j);
}

void get_path(int i, int j, int k) {
    path.clear();
    path.push_back(k);
    path.push_back(i);
    dfs(i, j);
    path.push_back(j);
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        // 用前一个状态算最小环
        // 至少包含三个点的环所经过的点的最大编号是k
        // 至少包含三个点, i, j, k 不重合
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                // 3倍的 INF 会爆int
                if (ans > 1LL * f[i][j] + g[i][k] + g[k][j]) {
                    ans = f[i][j] + g[i][k] + g[k][j];
                    get_path(i, j, k);
                }
            }
        }

        // 推 floyd
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // 略有不同
                if (f[i][j] > f[i][k] + f[k][j]) {
                    f[i][j] = f[i][k] + f[k][j];
                    pos[i][j] = k;
                }
            }
        }
    }
}
// endregion

// region 强制走 K 个边

void floyd(int a[][N], int b[][N]) {
    // temp数组作为相乘的结果
    static int temp[N][N];
    memset(temp, 0x3f, sizeof temp);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = min(temp[i][j], a[i][k] + b[k][j]);
            }
        }
    }

    memcpy(a, temp, sizeof temp);
}

void qsm() {
    memset(ans, 0x3f, sizeof ans);
    for (int i = 0; i < n; i++) ans[i][i] = 0;

    while (K) {
        if (K & 1) floyd(ans, f);
        floyd(f, f);
        K >>= 1;
    }
}
// endregion