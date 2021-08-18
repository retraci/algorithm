#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 31;

int n;
int va[10];
ll dp[N][N][N][N][N];

void solve() {
    memset(dp, 0, sizeof dp);
    dp[0][0][0][0][0] = 1;

    for (int a = 0; a <= va[0]; a++) {
        for (int b = 0; b <= va[1]; b++) {
            if (b > a) break;
            for (int c = 0; c <= va[2]; c++) {
                if (c > b) break;
                for (int d = 0; d <= va[3]; d++) {
                    if (d > c) break;
                    for (int e = 0; e <= va[4]; e++) {
                        if (e > d) break;

                        ll &p = dp[a][b][c][d][e];
                        if (a - 1 >= 0) p += dp[a - 1][b][c][d][e];
                        if (b - 1 >= 0) p += dp[a][b - 1][c][d][e];
                        if (c - 1 >= 0) p += dp[a][b][c - 1][d][e];
                        if (d - 1 >= 0) p += dp[a][b][c][d - 1][e];
                        if (e - 1 >= 0) p += dp[a][b][c][d][e - 1];
                    }
                }
            }
        }
    }

    cout << dp[va[0]][va[1]][va[2]][va[3]][va[4]] << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    while (cin >> n && n) {
        memset(va, 0, sizeof va);
        for (int i = 0; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}