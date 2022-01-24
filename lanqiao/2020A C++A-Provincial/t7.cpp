// 走方格

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 40;

int n, m;
int dp[N][N];

void solve() {
    memset(dp, 0, sizeof dp);

    dp[1][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!(i & 1) && !(j & 1)) continue;

            dp[i][j] += dp[i - 1][j] + dp[i][j - 1];
        }
    }

    cout << dp[n][m] << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> m;
    solve();

    return 0;
}