#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110;
const int M = 2e5 + 10;
const int BASE = 1e5 + 5;

int n;
int vw[N];
bool f[N][M];

void solve() {
    int s = 0;
    for (int i = 1; i <= n; i++) s += vw[i];

    memset(f, 0, sizeof f);
    f[0][0 + BASE] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = -s; j <= s; j++) {
            f[i][j + BASE] |= f[i - 1][j + BASE];

            if (j - vw[i] >= -s) f[i][j + BASE] |= f[i - 1][j - vw[i] + BASE];
            if (j + vw[i] <= s) f[i][j + BASE] |= f[i - 1][j + vw[i] + BASE];
        }
    }

    int ans = 0;
    for (int j = 1; j <= s; j++) if (f[n][j + BASE]) ans++;
    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &vw[i]);
    }
    solve();

    return 0;
}