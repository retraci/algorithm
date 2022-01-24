#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 55;

int n;
int maze[N][N];
int f[N][N][N][N];

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int a = 1; a <= n; a++) {
                for (int b = 1; b <= n; b++) {
                    f[i][j][a][b] = max({f[i - 1][j][a - 1][b],
                                         f[i][j - 1][a][b - 1],
                                         f[i - 1][j][a][b - 1],
                                         f[i][j - 1][a - 1][b]}) + maze[i][j] + maze[a][b];
                    if (i == a && j == b) {
                        f[i][j][a][b] -= maze[i][j];
                    }
                }
            }
        }
    }

    cout << f[n][n][n][n] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    int a, b, c;
    while (cin >> a >> b >> c, a) maze[a][b] = c;
    solve();

    return 0;
}