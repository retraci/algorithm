#include <bits/stdc++.h>

using namespace std;

const int maxn = 25;

int n;
int g[maxn][maxn];
int dp[1<<20][maxn];

void solve() {
    memset(dp, 0x3f, sizeof(dp));

    int lim = 1 << n;
    dp[1][0] = 0;
    for (int s = 1; s < lim; s++) {
        for (int v = 0; v < n; v++) {
            if (!(s >> v & 1)) continue;
            for (int u = 0; u < n; u++) {
                if (s >> u & 1)
                    dp[s][v] = min(dp[s][v], dp[s-(1<<v)][u] + g[u][v]);
            }
        }
    }

    cout << dp[lim-1][n-1] << endl;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &g[i][j]);
        }
    }
    solve();

    return 0;
}
