#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1010;
const int M = 210;

int n, m;
int w[M][M], qs[N];
int f[N][M][M];

void solve() {
    qs[0] = 1;
    memset(f, 0x3f, sizeof f);
    f[0][2][3] = 0;
    for (int i = 0; i < n; i++) {
        for (int b = 1; b <= m; b++) {
            for (int c = 1; c <= m; c++) {
                int a = qs[i], to = qs[i + 1];
                if (to != b && to != c && b != c) f[i + 1][b][c] = min(f[i + 1][b][c], f[i][b][c] + w[a][to]);
                if (to != a && to != c && a != c) f[i + 1][a][c] = min(f[i + 1][a][c], f[i][b][c] + w[b][to]);
                if (to != a && to != b && a != b) f[i + 1][b][a] = min(f[i + 1][b][a], f[i][b][c] + w[c][to]);
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int b = 1; b <= m; b++) {
        for (int c = 1; c <= m; c++) {
            ans = min(ans, f[n][b][c]);
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &w[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &qs[i]);
    }
    solve();

    return 0;
}