#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <vector>

using namespace std;

const int N = 35;

int n;
int va[N], vb[N];
bitset<N> mat[N];

// 异或方程
// r 为方程个数, c 为未知数个数, 返回方程组的解（多解 / 无解返回一个空的 vector）
// matrix[1~n]: 增广矩阵, 0 位置为常数
int gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c; col++) {
        for (int i = row; i <= r; i++) {
            if (mat[i][col] == 0) continue;
            swap(mat[row], mat[i]);
        }
        if (mat[row][col] == 0) continue;

        for (int i = 1; i <= r; i++) {
            if (i != row && mat[i][col]) mat[i] ^= mat[row];
        }
        row++;
    }

    int res = 1;
    for (int i = row; i <= r; i++) {
        if (mat[i][0] == 1) return -1;
        res <<= 1;
    }
    return res;
}

void solve() {
    for (int i = 1; i <= n; i++) mat[i].reset();
    // 最终状态
    for (int i = 1; i <= n; i++) {
        mat[i][0] = va[i] ^ vb[i];
    }
    // 式子 1
    for (int i = 1; i <= n; i++) mat[i][i] = 1;

    // 式子 2
    int x, y;
    while (cin >> x >> y, x || y) mat[y][x] = 1;

    int ans = gauss(n, n);
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