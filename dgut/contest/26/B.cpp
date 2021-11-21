#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>

using namespace std;

int n;
int g[22][22];

void solve() {
    int lim = 1 << n;
    int f[lim][n][2][2];
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; i++) {
        int ns = 1 << i;
        f[ns][i][0][0] = 0;
    }

    for (int mask = 0; mask < lim; mask++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= 1; j++) {
                for (int k = 0; k <= 1; k++) {
                    for (int v = 0; v < n; v++) {
                        if (mask >> v & 1) continue;

                        int ns = mask + (1 << v);
                        // 普通
                        f[ns][v][j][k] = min(f[ns][v][j][k], f[mask][i][j][k] + g[i][v]);
                        // 走路
                        if (j == 0) f[ns][v][1][k] = min(f[ns][v][1][k], f[mask][i][j][k]);
                        // 开飞机
                        if (k == 0) f[ns][v][j][1] = min(f[ns][v][j][1], f[mask][i][j][k] + 3 * g[i][v]);
                    }
                }
            }
        }
    }

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        ans = min(ans, f[lim - 1][i][1][1]);
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    solve();

    return 0;
}