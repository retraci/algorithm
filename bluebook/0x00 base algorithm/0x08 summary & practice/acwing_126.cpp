#include <bits/stdc++.h>

/*
 * 一维版本 acwing_55
 * */

using namespace std;

const int N = 110;

int n;
int arr[N][N];
int dp[N];

void solve() {
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            arr[i][j] += arr[i - 1][j];
        }
    }

    int ans = -0x3f3f3f3f;
    for (int sr = 1; sr <= n; sr++) {
        for (int tr = sr; tr <= n; tr++) {
            for (int j = 1; j <= n; j++) dp[j] = arr[tr][j] - arr[sr - 1][j];

            for (int j = 1; j <= n; j++) {
                dp[j] = max(dp[j], dp[j - 1] + dp[j]);
            }
            ans = max(ans, *max_element(dp + 1, dp + 1 + n));
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    cin >> n;
    for (int k = 0, x, y; k < n*n; k++) {
        x = k / n + 1, y = k % n + 1;
        cin >> arr[x][y];
    }
    solve();

    return 0;
}