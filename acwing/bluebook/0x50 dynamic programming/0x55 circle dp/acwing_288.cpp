#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 4000;

int n, m;
int w[N];
int f[2][N][2];

void solve() {
    int ans = 0;

    // n 小时不在睡觉
    memset(f, -0x3f, sizeof f);
    f[1 & 1][0][0] = f[1 & 1][1][1] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i & 1][j][0] = max(f[i - 1 & 1][j][0], f[i - 1 & 1][j][1]);
            if (j) {
                f[i & 1][j][1] = max(f[i - 1 & 1][j - 1][0], f[i - 1 & 1][j - 1][1] + w[i]);
            }
        }
    }
    ans = max(ans, f[n & 1][m][0]);

    // n 小时在睡觉
    memset(f, -0x3f, sizeof f);
    f[1 & 1][0][0] = 0, f[1 & 1][1][1] = w[1];
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i & 1][j][0] = max(f[i - 1 & 1][j][0], f[i - 1 & 1][j][1]);
            if (j) {
                f[i & 1][j][1] = max(f[i - 1 & 1][j - 1][0], f[i - 1 & 1][j - 1][1] + w[i]);
            }
        }
    }
    ans = max(ans, f[n & 1][m][1]);

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    solve();

    return 0;
}