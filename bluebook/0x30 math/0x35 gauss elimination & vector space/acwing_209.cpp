#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define ld long double

const int N = 510;
const ld eps = 1e-8;

int n, m;
int cs[N];
ld mat[N][N];
int ans;

// r 为方程数, c 为未知数数目
int gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c + 1; col++) {
        int cur = 0;
        for (int i = row; i <= r; i++) {
            if (fabs(mat[i][col]) > eps) {
                if (cur == 0 || cs[i] < cs[cur]) cur = i;
            }
        }
        if (cur == 0) continue;
        ans += cs[cur];
        for (int j = col; j <= c + 1; j++) swap(mat[cur][j], mat[row][j]);
        swap(cs[cur], cs[row]);

        for (int i = 1; i <= r; i++) {
            if (i != row && fabs(mat[i][col]) > eps) {
                ld rate = mat[i][col] / mat[row][col];
                for (int j = c + 1; j >= col; j--) {
                    mat[i][j] -= mat[row][j] * rate;
                }
            }
        }
        row++;
    }

    return row - 1;
}

void solve() {
    cout << gauss(n, m) << " " << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 1; i <= n; i++) cin >> cs[i];
    solve();

    return 0;
}