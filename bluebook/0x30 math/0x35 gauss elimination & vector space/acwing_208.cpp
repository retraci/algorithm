#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 35;

int n;
int va[N], vb[N];
int mat[N][N];

int gauss() {
    int r, c;
    for (r = 1, c = 1; c <= n; c++) {
        // 找主元
        int p = r;
        while (p <= n) {
            if (mat[p][c] != 0) break;
            else p++;
        }
        // 不一定有主元
        if (p > n) continue;
        // 交换到 r 行
        for (int j = c; j <= n + 1; j++) swap(mat[r][j], mat[p][j]);

        // 消元
        for (int i = r + 1; i <= n; i++) {
            // 如果 mat[i][c] 已经是 0, 则不需要消元
            if (mat[i][c] == 0) continue;
            for (int j = c; j <= n + 1; j++) {
                mat[i][j] ^= mat[r][j];
            }
        }
        r++;
    }

    int res = 1;
    for (int i = r; i <= n; i++) {
        // 全零行的右边出现非零 无解
        if (mat[i][n + 1]) return -1;
        res *= 2;
    }

    return res;
}

void solve() {
    memset(mat, 0, sizeof mat);
    // 最终状态
    for (int i = 1; i <= n; i++) {
        mat[i][n + 1] = va[i] ^ vb[i];
    }
    // 式子 1
    for (int i = 1; i <= n; i++) mat[i][i] = 1;

    // 式子 2
    int x, y;
    while (cin >> x >> y, x || y) {
        mat[y][x] = 1;
    }

    int ans = gauss();
    if (ans == -1) cout << "Oh,it's impossible~!!" << endl;
    else cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= n; i++) cin >> vb[i];
        solve();
    }

    return 0;
}