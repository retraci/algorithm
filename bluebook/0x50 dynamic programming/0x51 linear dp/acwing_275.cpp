#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 60;

int n, m;
int va[N][N];
int f[N][N][N][N];
int f2[2 * N][N][N];

void solve() {
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int a = 1; a <= n; a++) {
                for (int b = 1; b <= m; b++) {
                    int &v = f[i][j][a][b];
                    v = max(v, f[i - 1][j][a - 1][b] + va[i][j] + va[a][b]);
                    v = max(v, f[i - 1][j][a][b - 1] + va[i][j] + va[a][b]);
                    v = max(v, f[i][j - 1][a - 1][b] + va[i][j] + va[a][b]);
                    v = max(v, f[i][j - 1][a][b - 1] + va[i][j] + va[a][b]);
                    if (i == a && j == b) v -= va[i][j];
                }
            }
        }
    }
    cout << f[n][m][n][m] << endl;
}

void solve2() {
    memset(f2, 0, sizeof f2);
    for (int k = 2; k <= n + m; k++) {
        for (int i = 1; i <= n && i < k; i++) {
            for (int a = 1; a <= n && a < k; a++) {
                int j = k - i, b = k - a;
                int &v = f2[k][i][a];
                v = max(v, f2[k - 1][i][a] + va[i][j] + va[a][b]);
                v = max(v, f2[k - 1][i - 1][a - 1] + va[i][j] + va[a][b]);
                v = max(v, f2[k - 1][i - 1][a] + va[i][j] + va[a][b]);
                v = max(v, f2[k - 1][i][a - 1] + va[i][j] + va[a][b]);
                if (i == a && j == b) v -= va[i][j];
            }
        }
    }
    cout << f2[n + m][n][n] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &va[i][j]);
        }
    }
    solve2();

    return 0;
}